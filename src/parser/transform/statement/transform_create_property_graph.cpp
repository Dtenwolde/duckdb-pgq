#include "duckdb/parser/statement/create_statement.hpp"
#include "duckdb/parser/transformer.hpp"
#include "duckdb/parser/parsed_data/create_property_graph_info.hpp"
#include "duckdb/parser/tableref/basetableref.hpp"
#include "duckdb/parser/property_graph_table.hpp"
#include "duckdb/common/unordered_set.hpp"

namespace duckdb {

using namespace duckdb_libpgquery;

// unique_ptr<BaseTableRef> get_table_reference(string name) {
// 	auto tableref = make_unique<BaseTableRef>();
// 	tableref->table_name = table->name->relname;
// 	if (table->name->schemaname) {
// 		tableref->schema_name = table->name->schemaname;
// 	}
// 	return tableref;
// }

unique_ptr<PropertyGraphTable> Transformer::TranformPropertyGraphTable(PGPropertyGraphTable *table, unordered_set<string> &label_set) {
	// string
	// auto pg_table = make_unique<PropertyGraphTable>();
	// info->name = string(stmt->name);
	vector<string> keys, labels, source_key, destination_key;
	string name, source_key_reference, destination_key_reference;
	auto pg_table = make_unique<PropertyGraphTable>();
	auto qname = TransformQualifiedName(table->name);
	auto ref = TransformRangeVar(table->name);

	for (auto kc = table->keys->head; kc; kc = kc->next) {
		keys.push_back(string(reinterpret_cast<PGValue *>(kc->data.ptr_value)->val.str));
	}

	for (auto kc = table->labels->head; kc; kc = kc->next) {
		
		auto label = string(reinterpret_cast<PGValue *>(kc->data.ptr_value)->val.str);
		auto entry = label_set.find(label);
		if (entry == label_set.end()) {
			labels.push_back(label);
			label_set.insert(label);	
		}
		else {
			throw Exception("Labels need to be unique in PropertyGraph table. Label " + label + " has been repeated.");
		} 			
	}
	pg_table->name = qname.name;
	pg_table->keys = keys;
	pg_table->labels = labels;
	// pg_table->table = move(tableref);
	if (table->is_vertex_table) {
		// 	// info->vertex_tables.push_back()
		// 	info->vertex_tables.push_back(PropertyGraphTable(qname.name, keys, labels));
		// return 	make_unique<PropertyGraphTable>(keys, labels);
		// pg_table->keys = keys;
		// pg_table->labels = labels;
		// pg_table->table = move(tableref);
		pg_table->is_vertex_table = true;
		return pg_table;
		// return make_unique<PropertyGraphTable>(move(tableref), keys, labels);
		// return unique_ptr<PropertyGraphTable>(new PropertyGraphTable(keys, labels));
	} else {
		for (auto kc = table->source_key->head; kc; kc = kc->next) {
			source_key.push_back(string(reinterpret_cast<PGValue *>(kc->data.ptr_value)->val.str));
		}

		for (auto kc = table->destination_key->head; kc; kc = kc->next) {
			destination_key.push_back(string(reinterpret_cast<PGValue *>(kc->data.ptr_value)->val.str));
		}

		destination_key_reference = string(table->destination_key_reference->relname);
		source_key_reference = string(table->source_key_reference->relname);
		// Find a way to use reference
		pg_table->source_key = source_key;
		pg_table->source_key_reference = source_key_reference;
		pg_table->destination_key_reference = destination_key_reference;
		pg_table->destination_key = destination_key;
		pg_table->is_vertex_table = false;
		return pg_table;
		// return make_unique<PropertyGraphTable>(move(tableref), keys, labels, source_key, source_key_reference,
		//                                        destination_key, destination_key_reference);
		// auto pg_table = make_unique<PropertyGraphTable>;
		// pg_table->ref = move(ref);
		// return make_unique<PropertyGraphTable>(source_key_reference, destination_key_reference);
		// return unique_ptr<PropertyGraphTable>(new PropertyGraphTable(source_key_reference,
		// destination_key_reference));
		// look into make_unique. Do we need to modfiy Copy
		// info->edge_tables.push_back(pg_table);
	}
}

unique_ptr<CreateStatement> Transformer::TransformCreatePropertyGraph(PGNode *node) {
	D_ASSERT(node);
	D_ASSERT(node->type == T_PGCreatePropertyGraphStmt);

	auto stmt = reinterpret_cast<PGCreatePropertyGraphStmt *>(node);
	D_ASSERT(stmt);

	auto result = make_unique<CreateStatement>();
	auto info = make_unique<CreatePropertyGraphInfo>();
	unordered_set<string> label_set;

	info->name = string(stmt->name);
	info->on_conflict = OnCreateConflict::ERROR_ON_CONFLICT;
	// TransformExpressionList(stmt->vertex_tables);

	for (auto c = stmt->vertex_tables->head; c != NULL; c = lnext(c)) {
		auto node = reinterpret_cast<PGNode *>(c->data.ptr_value);
		switch (node->type) {

		case T_PGPropertyGraphTable: {
			auto graph_table = reinterpret_cast<PGPropertyGraphTable *>(c->data.ptr_value);
			auto qname = TransformQualifiedName(graph_table->name);
			auto pg_table = TranformPropertyGraphTable(graph_table, label_set);
			info->vertex_tables.push_back(move(pg_table));
			break;
		}
		// printf("%d", node->type);
		default:
			throw NotImplementedException("Node type not handled yet");
		}
	}

	for (auto c = stmt->edge_tables->head; c != NULL; c = lnext(c)) {
		auto node = reinterpret_cast<PGNode *>(c->data.ptr_value);
		switch (node->type) {

		case T_PGPropertyGraphTable: {
			auto graph_table = reinterpret_cast<PGPropertyGraphTable *>(c->data.ptr_value);
			// (void)graph_table;
			auto qname = TransformQualifiedName(graph_table->name);
			auto pg_table = TranformPropertyGraphTable(graph_table, label_set);
			info->edge_tables.push_back(move(pg_table));
			break;
		}
		default:
			throw NotImplementedException("ColumnDef type not handled yet");
		}
	}
	info->labels_set = label_set;
	result->info = move(info);
	return result;
}

} // namespace duckdb