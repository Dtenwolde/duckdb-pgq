#include "duckdb/parser/transformer.hpp"

namespace duckdb {
using namespace duckdb_libpgquery;

std::string Transformer::NodetypeToString(PGNodeTag type) {
	switch (type) {
	case T_PGInvalid:
		return "T_Invalid";
	case T_PGIndexInfo:
		return "T_IndexInfo";
	case T_PGExprContext:
		return "T_ExprContext";
	case T_PGProjectionInfo:
		return "T_ProjectionInfo";
	case T_PGJunkFilter:
		return "T_JunkFilter";
	case T_PGResultRelInfo:
		return "T_ResultRelInfo";
	case T_PGEState:
		return "T_EState";
	case T_PGTupleTableSlot:
		return "T_TupleTableSlot";
	case T_PGPlan:
		return "T_Plan";
	case T_PGResult:
		return "T_Result";
	case T_PGProjectSet:
		return "T_ProjectSet";
	case T_PGModifyTable:
		return "T_ModifyTable";
	case T_PGAppend:
		return "T_Append";
	case T_PGMergeAppend:
		return "T_MergeAppend";
	case T_PGRecursiveUnion:
		return "T_RecursiveUnion";
	case T_PGBitmapAnd:
		return "T_BitmapAnd";
	case T_PGBitmapOr:
		return "T_BitmapOr";
	case T_PGScan:
		return "T_Scan";
	case T_PGSeqScan:
		return "T_SeqScan";
	case T_PGSampleScan:
		return "T_SampleScan";
	case T_PGIndexScan:
		return "T_IndexScan";
	case T_PGIndexOnlyScan:
		return "T_IndexOnlyScan";
	case T_PGBitmapIndexScan:
		return "T_BitmapIndexScan";
	case T_PGBitmapHeapScan:
		return "T_BitmapHeapScan";
	case T_PGTidScan:
		return "T_TidScan";
	case T_PGSubqueryScan:
		return "T_SubqueryScan";
	case T_PGFunctionScan:
		return "T_FunctionScan";
	case T_PGValuesScan:
		return "T_ValuesScan";
	case T_PGTableFuncScan:
		return "T_TableFuncScan";
	case T_PGCteScan:
		return "T_CteScan";
	case T_PGNamedTuplestoreScan:
		return "T_NamedTuplestoreScan";
	case T_PGWorkTableScan:
		return "T_WorkTableScan";
	case T_PGForeignScan:
		return "T_ForeignScan";
	case T_PGCustomScan:
		return "T_CustomScan";
	case T_PGJoin:
		return "T_Join";
	case T_PGNestLoop:
		return "T_NestLoop";
	case T_PGMergeJoin:
		return "T_MergeJoin";
	case T_PGHashJoin:
		return "T_HashJoin";
	case T_PGMaterial:
		return "T_Material";
	case T_PGSort:
		return "T_Sort";
	case T_PGGroup:
		return "T_Group";
	case T_PGAgg:
		return "T_Agg";
	case T_PGWindowAgg:
		return "T_WindowAgg";
	case T_PGUnique:
		return "T_Unique";
	case T_PGGather:
		return "T_Gather";
	case T_PGGatherMerge:
		return "T_GatherMerge";
	case T_PGHash:
		return "T_Hash";
	case T_PGSetOp:
		return "T_SetOp";
	case T_PGLockRows:
		return "T_LockRows";
	case T_PGLimit:
		return "T_Limit";
	case T_PGNestLoopParam:
		return "T_NestLoopParam";
	case T_PGPlanRowMark:
		return "T_PlanRowMark";
	case T_PGPlanInvalItem:
		return "T_PlanInvalItem";
	case T_PGPlanState:
		return "T_PlanState";
	case T_PGResultState:
		return "T_ResultState";
	case T_PGProjectSetState:
		return "T_ProjectSetState";
	case T_PGModifyTableState:
		return "T_ModifyTableState";
	case T_PGAppendState:
		return "T_AppendState";
	case T_PGMergeAppendState:
		return "T_MergeAppendState";
	case T_PGRecursiveUnionState:
		return "T_RecursiveUnionState";
	case T_PGBitmapAndState:
		return "T_BitmapAndState";
	case T_PGBitmapOrState:
		return "T_BitmapOrState";
	case T_PGScanState:
		return "T_ScanState";
	case T_PGSeqScanState:
		return "T_SeqScanState";
	case T_PGSampleScanState:
		return "T_SampleScanState";
	case T_PGIndexScanState:
		return "T_IndexScanState";
	case T_PGIndexOnlyScanState:
		return "T_IndexOnlyScanState";
	case T_PGBitmapIndexScanState:
		return "T_BitmapIndexScanState";
	case T_PGBitmapHeapScanState:
		return "T_BitmapHeapScanState";
	case T_PGTidScanState:
		return "T_TidScanState";
	case T_PGSubqueryScanState:
		return "T_SubqueryScanState";
	case T_PGFunctionScanState:
		return "T_FunctionScanState";
	case T_PGTableFuncScanState:
		return "T_TableFuncScanState";
	case T_PGValuesScanState:
		return "T_ValuesScanState";
	case T_PGCteScanState:
		return "T_CteScanState";
	case T_PGNamedTuplestoreScanState:
		return "T_NamedTuplestoreScanState";
	case T_PGWorkTableScanState:
		return "T_WorkTableScanState";
	case T_PGForeignScanState:
		return "T_ForeignScanState";
	case T_PGCustomScanState:
		return "T_CustomScanState";
	case T_PGJoinState:
		return "T_JoinState";
	case T_PGNestLoopState:
		return "T_NestLoopState";
	case T_PGMergeJoinState:
		return "T_MergeJoinState";
	case T_PGHashJoinState:
		return "T_HashJoinState";
	case T_PGMaterialState:
		return "T_MaterialState";
	case T_PGSortState:
		return "T_SortState";
	case T_PGGroupState:
		return "T_GroupState";
	case T_PGAggState:
		return "T_AggState";
	case T_PGWindowAggState:
		return "T_WindowAggState";
	case T_PGUniqueState:
		return "T_UniqueState";
	case T_PGGatherState:
		return "T_GatherState";
	case T_PGGatherMergeState:
		return "T_GatherMergeState";
	case T_PGHashState:
		return "T_HashState";
	case T_PGSetOpState:
		return "T_SetOpState";
	case T_PGLockRowsState:
		return "T_LockRowsState";
	case T_PGLimitState:
		return "T_LimitState";
	case T_PGAlias:
		return "T_Alias";
	case T_PGRangeVar:
		return "T_RangeVar";
	case T_PGTableFunc:
		return "T_TableFunc";
	case T_PGExpr:
		return "T_Expr";
	case T_PGVar:
		return "T_Var";
	case T_PGConst:
		return "T_Const";
	case T_PGParam:
		return "T_Param";
	case T_PGAggref:
		return "T_Aggref";
	case T_PGGroupingFunc:
		return "T_GroupingFunc";
	case T_PGWindowFunc:
		return "T_WindowFunc";
	case T_PGArrayRef:
		return "T_ArrayRef";
	case T_PGFuncExpr:
		return "T_FuncExpr";
	case T_PGNamedArgExpr:
		return "T_NamedArgExpr";
	case T_PGOpExpr:
		return "T_OpExpr";
	case T_PGDistinctExpr:
		return "T_DistinctExpr";
	case T_PGNullIfExpr:
		return "T_NullIfExpr";
	case T_PGScalarArrayOpExpr:
		return "T_ScalarArrayOpExpr";
	case T_PGBoolExpr:
		return "T_BoolExpr";
	case T_PGSubLink:
		return "T_SubLink";
	case T_PGSubPlan:
		return "T_SubPlan";
	case T_PGAlternativeSubPlan:
		return "T_AlternativeSubPlan";
	case T_PGFieldSelect:
		return "T_FieldSelect";
	case T_PGFieldStore:
		return "T_FieldStore";
	case T_PGRelabelType:
		return "T_RelabelType";
	case T_PGCoerceViaIO:
		return "T_CoerceViaIO";
	case T_PGArrayCoerceExpr:
		return "T_ArrayCoerceExpr";
	case T_PGConvertRowtypeExpr:
		return "T_ConvertRowtypeExpr";
	case T_PGCollateExpr:
		return "T_CollateExpr";
	case T_PGCaseExpr:
		return "T_CaseExpr";
	case T_PGCaseWhen:
		return "T_CaseWhen";
	case T_PGCaseTestExpr:
		return "T_CaseTestExpr";
	case T_PGArrayExpr:
		return "T_ArrayExpr";
	case T_PGRowExpr:
		return "T_RowExpr";
	case T_PGRowCompareExpr:
		return "T_RowCompareExpr";
	case T_PGCoalesceExpr:
		return "T_CoalesceExpr";
	case T_PGMinMaxExpr:
		return "T_MinMaxExpr";
	case T_PGSQLValueFunction:
		return "T_SQLValueFunction";
	case T_PGXmlExpr:
		return "T_XmlExpr";
	case T_PGNullTest:
		return "T_NullTest";
	case T_PGBooleanTest:
		return "T_BooleanTest";
	case T_PGCoerceToDomain:
		return "T_CoerceToDomain";
	case T_PGCoerceToDomainValue:
		return "T_CoerceToDomainValue";
	case T_PGSetToDefault:
		return "T_SetToDefault";
	case T_PGCurrentOfExpr:
		return "T_CurrentOfExpr";
	case T_PGNextValueExpr:
		return "T_NextValueExpr";
	case T_PGInferenceElem:
		return "T_InferenceElem";
	case T_PGTargetEntry:
		return "T_TargetEntry";
	case T_PGRangeTblRef:
		return "T_RangeTblRef";
	case T_PGJoinExpr:
		return "T_JoinExpr";
	case T_PGFromExpr:
		return "T_FromExpr";
	case T_PGOnConflictExpr:
		return "T_OnConflictExpr";
	case T_PGIntoClause:
		return "T_IntoClause";
	case T_PGExprState:
		return "T_ExprState";
	case T_PGAggrefExprState:
		return "T_AggrefExprState";
	case T_PGWindowFuncExprState:
		return "T_WindowFuncExprState";
	case T_PGSetExprState:
		return "T_SetExprState";
	case T_PGSubPlanState:
		return "T_SubPlanState";
	case T_PGAlternativeSubPlanState:
		return "T_AlternativeSubPlanState";
	case T_PGDomainConstraintState:
		return "T_DomainConstraintState";
	case T_PGPlannerInfo:
		return "T_PlannerInfo";
	case T_PGPlannerGlobal:
		return "T_PlannerGlobal";
	case T_PGRelOptInfo:
		return "T_RelOptInfo";
	case T_PGIndexOptInfo:
		return "T_IndexOptInfo";
	case T_PGForeignKeyOptInfo:
		return "T_ForeignKeyOptInfo";
	case T_PGParamPathInfo:
		return "T_ParamPathInfo";
	case T_PGPath:
		return "T_Path";
	case T_PGIndexPath:
		return "T_IndexPath";
	case T_PGBitmapHeapPath:
		return "T_BitmapHeapPath";
	case T_PGBitmapAndPath:
		return "T_BitmapAndPath";
	case T_PGBitmapOrPath:
		return "T_BitmapOrPath";
	case T_PGTidPath:
		return "T_TidPath";
	case T_PGSubqueryScanPath:
		return "T_SubqueryScanPath";
	case T_PGForeignPath:
		return "T_ForeignPath";
	case T_PGCustomPath:
		return "T_CustomPath";
	case T_PGNestPath:
		return "T_NestPath";
	case T_PGMergePath:
		return "T_MergePath";
	case T_PGHashPath:
		return "T_HashPath";
	case T_PGAppendPath:
		return "T_AppendPath";
	case T_PGMergeAppendPath:
		return "T_MergeAppendPath";
	case T_PGResultPath:
		return "T_ResultPath";
	case T_PGMaterialPath:
		return "T_MaterialPath";
	case T_PGUniquePath:
		return "T_UniquePath";
	case T_PGGatherPath:
		return "T_GatherPath";
	case T_PGGatherMergePath:
		return "T_GatherMergePath";
	case T_PGProjectionPath:
		return "T_ProjectionPath";
	case T_PGProjectSetPath:
		return "T_ProjectSetPath";
	case T_PGSortPath:
		return "T_SortPath";
	case T_PGGroupPath:
		return "T_GroupPath";
	case T_PGUpperUniquePath:
		return "T_UpperUniquePath";
	case T_PGAggPath:
		return "T_AggPath";
	case T_PGGroupingSetsPath:
		return "T_GroupingSetsPath";
	case T_PGMinMaxAggPath:
		return "T_MinMaxAggPath";
	case T_PGWindowAggPath:
		return "T_WindowAggPath";
	case T_PGSetOpPath:
		return "T_SetOpPath";
	case T_PGRecursiveUnionPath:
		return "T_RecursiveUnionPath";
	case T_PGLockRowsPath:
		return "T_LockRowsPath";
	case T_PGModifyTablePath:
		return "T_ModifyTablePath";
	case T_PGLimitPath:
		return "T_LimitPath";
	case T_PGEquivalenceClass:
		return "T_EquivalenceClass";
	case T_PGEquivalenceMember:
		return "T_EquivalenceMember";
	case T_PGPathKey:
		return "T_PathKey";
	case T_PGPathTarget:
		return "T_PathTarget";
	case T_PGRestrictInfo:
		return "T_RestrictInfo";
	case T_PGPlaceHolderVar:
		return "T_PlaceHolderVar";
	case T_PGSpecialJoinInfo:
		return "T_SpecialJoinInfo";
	case T_PGAppendRelInfo:
		return "T_AppendRelInfo";
	case T_PGPartitionedChildRelInfo:
		return "T_PartitionedChildRelInfo";
	case T_PGPlaceHolderInfo:
		return "T_PlaceHolderInfo";
	case T_PGMinMaxAggInfo:
		return "T_MinMaxAggInfo";
	case T_PGPlannerParamItem:
		return "T_PlannerParamItem";
	case T_PGRollupData:
		return "T_RollupData";
	case T_PGGroupingSetData:
		return "T_GroupingSetData";
	case T_PGStatisticExtInfo:
		return "T_StatisticExtInfo";
	case T_PGMemoryContext:
		return "T_MemoryContext";
	case T_PGAllocSetContext:
		return "T_AllocSetContext";
	case T_PGSlabContext:
		return "T_SlabContext";
	case T_PGValue:
		return "T_Value";
	case T_PGInteger:
		return "T_Integer";
	case T_PGFloat:
		return "T_Float";
	case T_PGString:
		return "T_String";
	case T_PGBitString:
		return "T_BitString";
	case T_PGNull:
		return "T_Null";
	case T_PGList:
		return "T_List";
	case T_PGIntList:
		return "T_IntList";
	case T_PGOidList:
		return "T_OidList";
	case T_PGExtensibleNode:
		return "T_ExtensibleNode";
	case T_PGRawStmt:
		return "T_RawStmt";
	case T_PGQuery:
		return "T_Query";
	case T_PGPlannedStmt:
		return "T_PlannedStmt";
	case T_PGInsertStmt:
		return "T_InsertStmt";
	case T_PGDeleteStmt:
		return "T_DeleteStmt";
	case T_PGUpdateStmt:
		return "T_UpdateStmt";
	case T_PGSelectStmt:
		return "T_SelectStmt";
	case T_PGAlterTableStmt:
		return "T_AlterTableStmt";
	case T_PGAlterTableCmd:
		return "T_AlterTableCmd";
	case T_PGAlterDomainStmt:
		return "T_AlterDomainStmt";
	case T_PGSetOperationStmt:
		return "T_SetOperationStmt";
	case T_PGGrantStmt:
		return "T_GrantStmt";
	case T_PGGrantRoleStmt:
		return "T_GrantRoleStmt";
	case T_PGAlterDefaultPrivilegesStmt:
		return "T_AlterDefaultPrivilegesStmt";
	case T_PGClosePortalStmt:
		return "T_ClosePortalStmt";
	case T_PGClusterStmt:
		return "T_ClusterStmt";
	case T_PGCopyStmt:
		return "T_CopyStmt";
	case T_PGCreateStmt:
		return "T_CreateStmt";
	case T_PGDefineStmt:
		return "T_DefineStmt";
	case T_PGDropStmt:
		return "T_DropStmt";
	case T_PGTruncateStmt:
		return "T_TruncateStmt";
	case T_PGCommentStmt:
		return "T_CommentStmt";
	case T_PGFetchStmt:
		return "T_FetchStmt";
	case T_PGIndexStmt:
		return "T_IndexStmt";
	case T_PGCreatePropertyGraphStmt:
		return "T_CreatePropertyGraphStmt";
	case T_PGPropertyGraphTable:
		return "T_PropertyGraphTable"; // needs to be moved above
	case T_PGCreateFunctionStmt:
		return "T_CreateFunctionStmt";
	case T_PGAlterFunctionStmt:
		return "T_AlterFunctionStmt";
	case T_PGDoStmt:
		return "T_DoStmt";
	case T_PGRenameStmt:
		return "T_RenameStmt";
	case T_PGRuleStmt:
		return "T_RuleStmt";
	case T_PGNotifyStmt:
		return "T_NotifyStmt";
	case T_PGListenStmt:
		return "T_ListenStmt";
	case T_PGUnlistenStmt:
		return "T_UnlistenStmt";
	case T_PGTransactionStmt:
		return "T_TransactionStmt";
	case T_PGViewStmt:
		return "T_ViewStmt";
	case T_PGLoadStmt:
		return "T_LoadStmt";
	case T_PGCreateDomainStmt:
		return "T_CreateDomainStmt";
	case T_PGCreatedbStmt:
		return "T_CreatedbStmt";
	case T_PGDropdbStmt:
		return "T_DropdbStmt";
	case T_PGVacuumStmt:
		return "T_VacuumStmt";
	case T_PGExplainStmt:
		return "T_ExplainStmt";
	case T_PGCreateTableAsStmt:
		return "T_CreateTableAsStmt";
	case T_PGCreateSeqStmt:
		return "T_CreateSeqStmt";
	case T_PGAlterSeqStmt:
		return "T_AlterSeqStmt";
	case T_PGVariableSetStmt:
		return "T_VariableSetStmt";
	case T_PGVariableShowStmt:
		return "T_VariableShowStmt";
	case T_PGVariableShowSelectStmt:
		return "T_VariableShowSelectStmt";
	case T_PGDiscardStmt:
		return "T_DiscardStmt";
	case T_PGCreateTrigStmt:
		return "T_CreateTrigStmt";
	case T_PGCreatePLangStmt:
		return "T_CreatePLangStmt";
	case T_PGCreateRoleStmt:
		return "T_CreateRoleStmt";
	case T_PGAlterRoleStmt:
		return "T_AlterRoleStmt";
	case T_PGDropRoleStmt:
		return "T_DropRoleStmt";
	case T_PGLockStmt:
		return "T_LockStmt";
	case T_PGConstraintsSetStmt:
		return "T_ConstraintsSetStmt";
	case T_PGReindexStmt:
		return "T_ReindexStmt";
	case T_PGCheckPointStmt:
		return "T_CheckPointStmt";
	case T_PGCreateSchemaStmt:
		return "T_CreateSchemaStmt";
	case T_PGAlterDatabaseStmt:
		return "T_AlterDatabaseStmt";
	case T_PGAlterDatabaseSetStmt:
		return "T_AlterDatabaseSetStmt";
	case T_PGAlterRoleSetStmt:
		return "T_AlterRoleSetStmt";
	case T_PGCreateConversionStmt:
		return "T_CreateConversionStmt";
	case T_PGCreateCastStmt:
		return "T_CreateCastStmt";
	case T_PGCreateOpClassStmt:
		return "T_CreateOpClassStmt";
	case T_PGCreateOpFamilyStmt:
		return "T_CreateOpFamilyStmt";
	case T_PGAlterOpFamilyStmt:
		return "T_AlterOpFamilyStmt";
	case T_PGPrepareStmt:
		return "T_PrepareStmt";
	case T_PGExecuteStmt:
		return "T_ExecuteStmt";
	case T_PGCallStmt:
		return "T_CallStmt";
	case T_PGDeallocateStmt:
		return "T_DeallocateStmt";
	case T_PGDeclareCursorStmt:
		return "T_DeclareCursorStmt";
	case T_PGCreateTableSpaceStmt:
		return "T_CreateTableSpaceStmt";
	case T_PGDropTableSpaceStmt:
		return "T_DropTableSpaceStmt";
	case T_PGAlterObjectDependsStmt:
		return "T_AlterObjectDependsStmt";
	case T_PGAlterObjectSchemaStmt:
		return "T_AlterObjectSchemaStmt";
	case T_PGAlterOwnerStmt:
		return "T_AlterOwnerStmt";
	case T_PGAlterOperatorStmt:
		return "T_AlterOperatorStmt";
	case T_PGDropOwnedStmt:
		return "T_DropOwnedStmt";
	case T_PGReassignOwnedStmt:
		return "T_ReassignOwnedStmt";
	case T_PGCompositeTypeStmt:
		return "T_CompositeTypeStmt";
	case T_PGCreateEnumStmt:
		return "T_CreateEnumStmt";
	case T_PGCreateRangeStmt:
		return "T_CreateRangeStmt";
	case T_PGAlterEnumStmt:
		return "T_AlterEnumStmt";
	case T_PGAlterTSDictionaryStmt:
		return "T_AlterTSDictionaryStmt";
	case T_PGAlterTSConfigurationStmt:
		return "T_AlterTSConfigurationStmt";
	case T_PGCreateFdwStmt:
		return "T_CreateFdwStmt";
	case T_PGAlterFdwStmt:
		return "T_AlterFdwStmt";
	case T_PGCreateForeignServerStmt:
		return "T_CreateForeignServerStmt";
	case T_PGAlterForeignServerStmt:
		return "T_AlterForeignServerStmt";
	case T_PGCreateUserMappingStmt:
		return "T_CreateUserMappingStmt";
	case T_PGAlterUserMappingStmt:
		return "T_AlterUserMappingStmt";
	case T_PGDropUserMappingStmt:
		return "T_DropUserMappingStmt";
	case T_PGAlterTableSpaceOptionsStmt:
		return "T_AlterTableSpaceOptionsStmt";
	case T_PGAlterTableMoveAllStmt:
		return "T_AlterTableMoveAllStmt";
	case T_PGSecLabelStmt:
		return "T_SecLabelStmt";
	case T_PGCreateForeignTableStmt:
		return "T_CreateForeignTableStmt";
	case T_PGImportForeignSchemaStmt:
		return "T_ImportForeignSchemaStmt";
	case T_PGCreateExtensionStmt:
		return "T_CreateExtensionStmt";
	case T_PGAlterExtensionStmt:
		return "T_AlterExtensionStmt";
	case T_PGAlterExtensionContentsStmt:
		return "T_AlterExtensionContentsStmt";
	case T_PGCreateEventTrigStmt:
		return "T_CreateEventTrigStmt";
	case T_PGAlterEventTrigStmt:
		return "T_AlterEventTrigStmt";
	case T_PGRefreshMatViewStmt:
		return "T_RefreshMatViewStmt";
	case T_PGReplicaIdentityStmt:
		return "T_ReplicaIdentityStmt";
	case T_PGAlterSystemStmt:
		return "T_AlterSystemStmt";
	case T_PGCreatePolicyStmt:
		return "T_CreatePolicyStmt";
	case T_PGAlterPolicyStmt:
		return "T_AlterPolicyStmt";
	case T_PGCreateTransformStmt:
		return "T_CreateTransformStmt";
	case T_PGCreateAmStmt:
		return "T_CreateAmStmt";
	case T_PGCreatePublicationStmt:
		return "T_CreatePublicationStmt";
	case T_PGAlterPublicationStmt:
		return "T_AlterPublicationStmt";
	case T_PGCreateSubscriptionStmt:
		return "T_CreateSubscriptionStmt";
	case T_PGAlterSubscriptionStmt:
		return "T_AlterSubscriptionStmt";
	case T_PGDropSubscriptionStmt:
		return "T_DropSubscriptionStmt";
	case T_PGCreateStatsStmt:
		return "T_CreateStatsStmt";
	case T_PGAlterCollationStmt:
		return "T_AlterCollationStmt";
	case T_PGAExpr:
		return "TAExpr";
	case T_PGColumnRef:
		return "T_ColumnRef";
	case T_PGParamRef:
		return "T_ParamRef";
	case T_PGAConst:
		return "TAConst";
	case T_PGFuncCall:
		return "T_FuncCall";
	case T_PGAStar:
		return "TAStar";
	case T_PGAIndices:
		return "TAIndices";
	case T_PGAIndirection:
		return "TAIndirection";
	case T_PGAArrayExpr:
		return "TAArrayExpr";
	case T_PGResTarget:
		return "T_ResTarget";
	case T_PGMultiAssignRef:
		return "T_MultiAssignRef";
	case T_PGTypeCast:
		return "T_TypeCast";
	case T_PGCollateClause:
		return "T_CollateClause";
	case T_PGSortBy:
		return "T_SortBy";
	case T_PGWindowDef:
		return "T_WindowDef";
	case T_PGRangeSubselect:
		return "T_RangeSubselect";
	case T_PGRangeFunction:
		return "T_RangeFunction";
	case T_PGRangeTableSample:
		return "T_RangeTableSample";
	case T_PGRangeTableFunc:
		return "T_RangeTableFunc";
	case T_PGRangeTableFuncCol:
		return "T_RangeTableFuncCol";
	case T_PGTypeName:
		return "T_TypeName";
	case T_PGColumnDef:
		return "T_ColumnDef";
	case T_PGIndexElem:
		return "T_IndexElem";
	case T_PGConstraint:
		return "T_Constraint";
	case T_PGDefElem:
		return "T_DefElem";
	case T_PGRangeTblEntry:
		return "T_RangeTblEntry";
	case T_PGRangeTblFunction:
		return "T_RangeTblFunction";
	case T_PGTableSampleClause:
		return "T_TableSampleClause";
	case T_PGWithCheckOption:
		return "T_WithCheckOption";
	case T_PGSortGroupClause:
		return "T_SortGroupClause";
	case T_PGGroupingSet:
		return "T_GroupingSet";
	case T_PGWindowClause:
		return "T_WindowClause";
	case T_PGObjectWithArgs:
		return "T_ObjectWithArgs";
	case T_PGAccessPriv:
		return "T_AccessPriv";
	case T_PGCreateOpClassItem:
		return "T_CreateOpClassItem";
	case T_PGTableLikeClause:
		return "T_TableLikeClause";
	case T_PGFunctionParameter:
		return "T_FunctionParameter";
	case T_PGLockingClause:
		return "T_LockingClause";
	case T_PGRowMarkClause:
		return "T_RowMarkClause";
	case T_PGXmlSerialize:
		return "T_XmlSerialize";
	case T_PGWithClause:
		return "T_WithClause";
	case T_PGInferClause:
		return "T_InferClause";
	case T_PGOnConflictClause:
		return "T_OnConflictClause";
	case T_PGCommonTableExpr:
		return "T_CommonTableExpr";
	case T_PGRoleSpec:
		return "T_RoleSpec";
	case T_PGTriggerTransition:
		return "T_TriggerTransition";
	case T_PGPartitionElem:
		return "T_PartitionElem";
	case T_PGPartitionSpec:
		return "T_PartitionSpec";
	case T_PGPartitionBoundSpec:
		return "T_PartitionBoundSpec";
	case T_PGPartitionRangeDatum:
		return "T_PartitionRangeDatum";
	case T_PGPartitionCmd:
		return "T_PartitionCmd";
	case T_PGIdentifySystemCmd:
		return "T_IdentifySystemCmd";
	case T_PGBaseBackupCmd:
		return "T_BaseBackupCmd";
	case T_PGCreateReplicationSlotCmd:
		return "T_CreateReplicationSlotCmd";
	case T_PGDropReplicationSlotCmd:
		return "T_DropReplicationSlotCmd";
	case T_PGStartReplicationCmd:
		return "T_StartReplicationCmd";
	case T_PGTimeLineHistoryCmd:
		return "T_TimeLineHistoryCmd";
	case T_PGSQLCmd:
		return "T_SQLCmd";
	case T_PGTriggerData:
		return "T_TriggerData";
	case T_PGEventTriggerData:
		return "T_EventTriggerData";
	case T_PGReturnSetInfo:
		return "T_ReturnSetInfo";
	case T_PGWindowObjectData:
		return "T_WindowObjectData";
	case T_PGTIDBitmap:
		return "T_TIDBitmap";
	case T_PGInlineCodeBlock:
		return "T_InlineCodeBlock";
	case T_PGFdwRoutine:
		return "T_FdwRoutine";
	case T_PGIndexAmRoutine:
		return "T_IndexAmRoutine";
	case T_PGTsmRoutine:
		return "T_TsmRoutine";
	case T_PGForeignKeyCacheInfo:
		return "T_ForeignKeyCacheInfo";
	default:
		D_ASSERT(0);
		return "";
	}
}

} // namespace duckdb
