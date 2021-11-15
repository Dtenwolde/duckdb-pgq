#include "duckdb/function/scalar/sql_pgq_functions.hpp"
#include "duckdb/planner/expression/bound_function_expression.hpp"
#include "duckdb/common/vector_operations/vector_operations.hpp"
#include "duckdb/execution/expression_executor.hpp"
#include "duckdb/main/client_context.hpp"
#include "duckdb/common/vector_operations/vector_operations.hpp"
#include "duckdb/common/pair.hpp"

namespace duckdb {

struct MsbfsBindData : public FunctionData {
	ClientContext &context;
	// int32_t num_bfs;

	MsbfsBindData(ClientContext &context) : context(context) {
	}


	~MsbfsBindData() {
		// delete [] context.csr_list[0]->v;
	}

	unique_ptr<FunctionData> Copy() override {
		return make_unique<MsbfsBindData>(context);
	}
};

// static bool check_empty_bitset(vector<int64_t> set_list) {
// 	bool ans = true;
// 	// int64_t sum = 0;
// 	for(auto set: set_list) {
// 		// sum = sum + set;
// 		if(set > 0) {
// 			ans = false;
// 			break;
// 		}
// 	}
// 	return ans;
// }

static bool is_bit_set(uint32_t num, uint8_t bit)
{
    return 1 == ( (num >> bit) & 1);
}

static void msbfs_function(DataChunk &args, ExpressionState &state, Vector &result) {
	// D_ASSERT(args.ColumnCount() == 0);
	auto &func_expr = (BoundFunctionExpression &)state.expr;
	auto &info = (MsbfsBindData &)*func_expr.bind_info;

	// int64_t num_bfs = args.data[0].GetValue(0).GetValue<int64_t>();
	int64_t input_size = args.data[1].GetValue(0).GetValue<int64_t>();

	auto &src = args.data[2];
	// .GetValue(0).GetValue<int64_t>();

	VectorData vdata_src, vdata_target;
	src.Orrify(args.size(), vdata_src);

	auto src_data = (int64_t *)vdata_src.data;

	auto &target = args.data[3];
	// .GetValue(0).GetValue<int64_t>();
	target.Orrify(args.size(), vdata_target);
	auto target_data = (int64_t *)vdata_target.data;
	// const int32_t bfs = info.num_bfs;
	
	int8_t result_size = 0;
	idx_t curr_batch = 0;
	result.vector_type = VectorType::FLAT_VECTOR;
	auto result_data = FlatVector::GetData<bool>(result);

	while (curr_batch < args.size()) {
		int8_t lanes = 0;
		vector<int64_t> seen(input_size);
		// vector<std::bitset<LANE_LIMIT>> seen(input_size);

		// vector<std::bitset<LANE_LIMIT>> visit(input_size);
		vector<int64_t> visit_next(input_size);
		vector<int64_t> visit(input_size);
		// vector<int64_t> visit_next(input_size);
		// value -> lane_index, src_indexes 
		unordered_map<int64_t, pair<int8_t, vector<int64_t>>> lane_map;
	

	for(idx_t i =  curr_batch; i <  args.size() && lanes < LANE_LIMIT ; i++) {
		auto entry = lane_map.find(src_data[i]);
		if(entry == lane_map.end()) {
			lane_map[src_data[i]].first = lanes;
			seen[lanes] = pow(2, lanes); 
			visit[lanes] = pow(2, lanes);
			// seen[lanes] = std::bitset<LANE_LIMIT>();
			// seen[lanes][i] = 1;
			// seen[lanes] = std::bitset<LANE_LIMIT>{""}; 
			// visit[lanes] = pow(2, lanes);
			// seen[src_data[i]] = pow(2, lanes);
			// visit[src_data[i]] = pow(2, lanes);
			lanes++;
		}
			lane_map[src_data[i]].second.push_back(i);
			result_size++;
	}
	
	// for (auto i = 0, idx = 0; i < lanes && idx < (int32_t)args.size(); i++, idx++) {
	// 	seen[src_data[idx]] = pow(2, i);
	// 	visit[src_data[idx]] = pow(2, i);
	// }
	// bool init = true;
	int64_t d = 1;
	// while(!check_empty_bitset(visit)) {
	vector<int64_t> visit_list;
	size_t visit_limit = input_size / 2;
	int mode = 0;
	size_t visit_count = 0;
	while (d > 0 ) {
		// init = false;
		d = 0;
		
		// if(visit_list.size() > visit_limit) {
		// 	mode = 2;
		// 	visit_list.clear();
			// visit_count = 0;
		// }
		if(visit_count < visit_limit) {
			mode = 0;
		}
		if(mode == 1) {
			auto visit_list_copy = visit_list;
			visit_list.clear();
			auto csr = move(info.context.csr_list[0]);

			for(auto i : visit_list_copy) {
				// if(i > csr->v)
				for (auto index = (long)csr->v[i]; index < (long)csr->v[i + 1]; index++) {
					auto n = csr->e[index];
					visit_next[n] = visit_next[n] | visit[i];
					if(visit_next[n]) {
						visit_list.push_back(n);
					}
				}
				visit_list_copy.clear();
			}
			info.context.csr_list[0] = move(csr);

			visit_list_copy = visit_list;
			visit_list.clear();
			visit_count = 0;
			for (auto i: visit_list_copy) {
				// visit_list_copy = visit_list;
				visit_next[i] = visit_next[i] & ~seen[i];
				seen[i] = seen[i] | visit_next[i];
				if(d == 0 && visit_next[i]) {
					d = 1;
				
				}
				if(visit_next[i]) {
					visit_count++;
					visit_list.push_back(i);
				}
					
			}

			visit = visit_next;
			for (auto i = 0; i < input_size; i++) {
				visit_next[i] = 0;
			}
		}
		if(mode == 2 || mode == 0) {

			visit_count = 0;
			for (int64_t i = 0; i < input_size - 1; i++) {
				if (!visit[i])
					continue;
				auto csr = move(info.context.csr_list[0]);
				// if(i > csr->v)
				for (auto index = (long)csr->v[i]; index < (long)csr->v[i + 1]; index++) {
					auto n = csr->e[index];
					visit_next[n] = visit_next[n] | visit[i];
					if(visit_next[n]) {
						visit_count++;
						if(mode == 0) {
							visit_list.push_back(n);
						}
					}
						
					// seen[i] = seen[i] | visit_next[i];
					// if(visit_next[n])
					// 	d = 1;
				}
				info.context.csr_list[0] = move(csr);
			}
			if(mode == 0){
				if(visit_list.size() > 0)
					mode = 1;
			}
			for (int64_t i = 0; i < input_size ; i++) {
				if (!visit_next[i])
					continue;
				visit_next[i] = visit_next[i] & ~seen[i];
				seen[i] = seen[i] | visit_next[i];
				if(d == 0 && visit_next[i] )
					d = 1;
					
			}

			visit = visit_next;
			for (auto i = 0; i < input_size; i++) {
				visit_next[i] = 0;
			}
		}
		// check target
		// visit_list with n's to keep track (iniitally 64 nodes to visit but looping till input_size)
		// top down vs bottom up ->
		// adaptive with and without visit list-> benchmark
	}

	
	// auto &result_mask = FlatVector::Nullmask(result);

	for (auto iter : lane_map) {
    //   cout << x.first << " " << x.second << endl;
		auto value = iter.first;
		auto bfs_num = iter.second.first;
		auto pos = iter.second.second;
		for(auto index: pos) {
			if(is_bit_set(seen[target_data[index]], bfs_num) & is_bit_set(seen[value], bfs_num) ) {
				result_data[index] = true;
			}
			else
				result_data[index] = false;
		}
	}
	curr_batch = curr_batch + result_size;
	}
	// for (idx_t i = 0; i < lanes; i++) {
	// 	auto entry = lane_map.find(src_data[i]);
	// 	if ((seen[src_data[i]] & seen[target_data[i]]) == 0) {
	// 		result_data[i] = false;
	// 	} else {
	// 		result_data[i] = true;
	// 	}
	// }

	// local struct -> bitset (how many bits it contains), 
				// dynamically move between different ; can
				// 3 modes to benchmark - separate visit list ( keep track of number of nodes to visit) 
				// if nodes < count/threshold, then only use  
				// 
				// combine same source --> suboptisation 
				// allocate one lane per unique src. 
				// remember mapping of lanes to src. for loop to discover if already seen map it to that; 
				// doing sort -> not worth it ; could look into hash table. 

				// what if seen takes up too much memory ? will have to drop elements. 
				// LRU or hit count for eviction from  caching. 
				// count how often sources reoccur; first run non popular sources, then popular ones at end. 
				// immediately answer for those frequent sources. 

				// shortest path - dynamically change bit size based on distance. 
				// start with bit_size 8, if distance becomes too big 
				// copy current search state to 16 bit and resume implementation. 
				// hops using msbfs -> 
				// weights supported. 
				// 32 bit floats for storing weights --> implementations faster.  



				// interpret bi directional edges, 
				// pass flag undirected or any directed. 
				// unless explicitly given ; edge has two IDs if we support undirected edges.
				// bi directional - SQL query union all (unidirectional, duplicate edges )
				// every edge user puts in edge table is bi directional assumption ( different mode)
				// TODO: bi directional mode. 
				// two group by - one for src dense IDs, one for dest dense IDs and then do a sum of both. 
				//  
				// multiple edges across vertices can be supported. 
				// d = visit[i] & ~seen[n];
				// if (d > 0) {
				// 	visit_next[n] = visit_next[n] | d;
				// 	seen[n] = seen[n] | d;
				// }
}

static unique_ptr<FunctionData> msbfs_bind(ClientContext &context, ScalarFunction &bound_function,
                                           vector<unique_ptr<Expression>> &arguments) {
	// 	// SequenceCatalogEntry *sequence = nullptr;
	// 	if (!arguments[0]->IsFoldable()) {
	// 		throw InvalidInputException("Id must be constant.");
	// 	}

	// 	Value num_bfs = ExpressionExecutor::EvaluateScalar(*arguments[0]);

	return make_unique<MsbfsBindData>(context);
}

void MsBfsFun::RegisterFunction(BuiltinFunctions &set) {
	// padding reqd for csr_v ; size unequal
	// id, v_size, source, target
	set.AddFunction(ScalarFunction(
	    "reachability", {LogicalType::INTEGER, LogicalType::BIGINT, LogicalType::BIGINT, LogicalType::BIGINT},
	    LogicalType::BOOLEAN, msbfs_function, false, msbfs_bind));
}

} // namespace duckdb