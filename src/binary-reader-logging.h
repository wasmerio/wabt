/*
 * Copyright 2017 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WABT_BINARY_READER_LOGGING_H_
#define WABT_BINARY_READER_LOGGING_H_

#include "src/binary-reader.h"

namespace wabt {

class Stream;

class BinaryReaderLogging : public BinaryReaderDelegate {
 public:
  BinaryReaderLogging(Stream*, BinaryReaderDelegate* forward);

  bool OnError(const Error&) override;
  void OnSetState(const State* s) override;

  Result BeginModule(uint32_t version) override;
  Result EndModule() override;

  Result BeginSection(Index section_index,
                      BinarySection section_type,
                      Offset size) override;

  Result BeginCustomSection(Offset size, string_view section_name) override;
  Result EndCustomSection() override;

  Result BeginTypeSection(Offset size) override;
  Result OnTypeCount(Index count) override;
  Result OnType(Index index,
                Index param_count,
                Type* param_types,
                Index result_count,
                Type* result_types) override;
  Result EndTypeSection() override;

  Result BeginImportSection(Offset size) override;
  Result OnImportCount(Index count) override;
  Result OnImport(Index index,
                  string_view module_name,
                  string_view field_name) override;
  Result OnImportFunc(Index import_index,
                      string_view module_name,
                      string_view field_name,
                      Index func_index,
                      Index sig_index) override;
  Result OnImportTable(Index import_index,
                       string_view module_name,
                       string_view field_name,
                       Index table_index,
                       Type elem_type,
                       const Limits* elem_limits) override;
  Result OnImportMemory(Index import_index,
                        string_view module_name,
                        string_view field_name,
                        Index memory_index,
                        const Limits* page_limits) override;
  Result OnImportGlobal(Index import_index,
                        string_view module_name,
                        string_view field_name,
                        Index global_index,
                        Type type,
                        bool mutable_) override;
  Result OnImportEvent(Index import_index,
                       string_view module_name,
                       string_view field_name,
                       Index event_index,
                       Index sig_index) override;
  Result EndImportSection() override;

  Result BeginFunctionSection(Offset size) override;
  Result OnFunctionCount(Index count) override;
  Result OnFunction(Index index, Index sig_index) override;
  Result EndFunctionSection() override;

  Result BeginTableSection(Offset size) override;
  Result OnTableCount(Index count) override;
  Result OnTable(Index index,
                 Type elem_type,
                 const Limits* elem_limits) override;
  Result EndTableSection() override;

  Result BeginMemorySection(Offset size) override;
  Result OnMemoryCount(Index count) override;
  Result OnMemory(Index index, const Limits* limits) override;
  Result EndMemorySection() override;

  Result BeginGlobalSection(Offset size) override;
  Result OnGlobalCount(Index count) override;
  Result BeginGlobal(Index index, Type type, bool mutable_) override;
  Result BeginGlobalInitExpr(Index index) override;
  Result EndGlobalInitExpr(Index index) override;
  Result EndGlobal(Index index) override;
  Result EndGlobalSection() override;

  Result BeginExportSection(Offset size) override;
  Result OnExportCount(Index count) override;
  Result OnExport(Index index,
                  ExternalKind kind,
                  Index item_index,
                  string_view name) override;
  Result EndExportSection() override;

  Result BeginStartSection(Offset size) override;
  Result OnStartFunction(Index func_index) override;
  Result EndStartSection() override;

  Result BeginCodeSection(Offset size) override;
  Result OnFunctionBodyCount(Index count) override;
  Result BeginFunctionBody(Index index, Offset size) override;
  Result OnLocalDeclCount(Index count) override;
  Result OnLocalDecl(Index decl_index, Index count, Type type) override;

  Result OnOpcode(Opcode opcode) override;
  Result OnOpcodeBare() override;
  Result OnOpcodeIndex(Index value) override;
  Result OnOpcodeIndexIndex(Index value, Index value2) override;
  Result OnOpcodeUint32(uint32_t value) override;
  Result OnOpcodeUint32Uint32(uint32_t value, uint32_t value2) override;
  Result OnOpcodeUint64(uint64_t value) override;
  Result OnOpcodeF32(uint32_t value) override;
  Result OnOpcodeF64(uint64_t value) override;
  Result OnOpcodeV128(v128 value) override;
  Result OnOpcodeBlockSig(Type sig_type) override;
  Result OnAtomicLoadExpr(Opcode opcode,
                          uint32_t alignment_log2,
                          Address offset) override;
  Result OnAtomicStoreExpr(Opcode opcode,
                           uint32_t alignment_log2,
                           Address offset) override;
  Result OnAtomicRmwExpr(Opcode opcode,
                         uint32_t alignment_log2,
                         Address offset) override;
  Result OnAtomicRmwCmpxchgExpr(Opcode opcode,
                                uint32_t alignment_log2,
                                Address offset) override;
  Result OnBinaryExpr(Opcode opcode) override;
  Result OnBlockExpr(Type sig_type) override;
  Result OnBrExpr(Index depth) override;
  Result OnBrIfExpr(Index depth) override;
  Result OnBrOnExnExpr(Index depth, Index event_index) override;
  Result OnBrTableExpr(Index num_targets,
                       Index* target_depths,
                       Index default_target_depth) override;
  Result OnCallExpr(Index func_index) override;
  Result OnCatchExpr() override;
  Result OnCallIndirectExpr(Index sig_index, Index table_index) override;
  Result OnCompareExpr(Opcode opcode) override;
  Result OnConvertExpr(Opcode opcode) override;
  Result OnDropExpr() override;
  Result OnElseExpr() override;
  Result OnEndExpr() override;
  Result OnEndFunc() override;
  Result OnF32ConstExpr(uint32_t value_bits) override;
  Result OnF64ConstExpr(uint64_t value_bits) override;
  Result OnV128ConstExpr(v128 value_bits) override;
  Result OnGlobalGetExpr(Index global_index) override;
  Result OnGlobalSetExpr(Index global_index) override;
  Result OnI32ConstExpr(uint32_t value) override;
  Result OnI64ConstExpr(uint64_t value) override;
  Result OnIfExpr(Type sig_type) override;
  Result OnLoadExpr(Opcode opcode,
                    uint32_t alignment_log2,
                    Address offset) override;
  Result OnLocalGetExpr(Index local_index) override;
  Result OnLocalSetExpr(Index local_index) override;
  Result OnLocalTeeExpr(Index local_index) override;
  Result OnLoopExpr(Type sig_type) override;
  Result OnMemoryCopyExpr() override;
  Result OnDataDropExpr(Index segment_index) override;
  Result OnMemoryFillExpr() override;
  Result OnMemoryGrowExpr() override;
  Result OnMemoryInitExpr(Index segment_index) override;
  Result OnMemorySizeExpr() override;
  Result OnTableCopyExpr() override;
  Result OnElemDropExpr(Index segment_index) override;
  Result OnTableInitExpr(Index segment_index) override;
  Result OnTableGetExpr(Index table) override;
  Result OnTableSetExpr(Index table) override;
  Result OnTableGrowExpr(Index table) override;
  Result OnTableSizeExpr(Index table) override;
  Result OnRefNullExpr() override;
  Result OnRefIsNullExpr() override;
  Result OnNopExpr() override;
  Result OnRethrowExpr() override;
  Result OnReturnCallExpr(Index func_index) override;
  Result OnReturnCallIndirectExpr(Index sig_index, Index table_index) override;
  Result OnReturnExpr() override;
  Result OnSelectExpr() override;
  Result OnStoreExpr(Opcode opcode,
                     uint32_t alignment_log2,
                     Address offset) override;
  Result OnThrowExpr(Index event_index) override;
  Result OnTryExpr(Type sig_type) override;
  Result OnUnaryExpr(Opcode opcode) override;
  Result OnTernaryExpr(Opcode opcode) override;
  Result OnUnreachableExpr() override;
  Result OnAtomicWaitExpr(Opcode opcode,
                          uint32_t alignment_log2,
                          Address offset) override;
  Result OnAtomicNotifyExpr(Opcode opcode,
                            uint32_t alignment_log2,
                            Address offset) override;
  Result EndFunctionBody(Index index) override;
  Result EndCodeSection() override;
  Result OnSimdLaneOpExpr(Opcode opcode, uint64_t value) override;
  Result OnSimdShuffleOpExpr(Opcode opcode, v128 value) override;

  Result BeginElemSection(Offset size) override;
  Result OnElemSegmentCount(Index count) override;
  Result BeginElemSegment(Index index,
                          Index table_index,
                          bool passive,
                          Type elem_type) override;
  Result BeginElemSegmentInitExpr(Index index) override;
  Result EndElemSegmentInitExpr(Index index) override;
  Result OnElemSegmentElemExprCount(Index index, Index count) override;
  Result OnElemSegmentElemExpr_RefNull(Index segment_index) override;
  Result OnElemSegmentElemExpr_RefFunc(Index segment_index,
                                       Index func_index) override;
  Result EndElemSegment(Index index) override;
  Result EndElemSection() override;

  Result BeginDataSection(Offset size) override;
  Result OnDataSegmentCount(Index count) override;
  Result BeginDataSegment(Index index, Index memory_index, bool passive) override;
  Result BeginDataSegmentInitExpr(Index index) override;
  Result EndDataSegmentInitExpr(Index index) override;
  Result OnDataSegmentData(Index index,
                           const void* data,
                           Address size) override;
  Result EndDataSegment(Index index) override;
  Result EndDataSection() override;

  Result BeginDataCountSection(Offset size) override;
  Result OnDataCount(Index count) override;
  Result EndDataCountSection() override;

  Result BeginNamesSection(Offset size) override;
  Result OnModuleNameSubsection(Index index,
                                uint32_t name_type,
                                Offset subsection_size) override;
  Result OnModuleName(string_view name) override;
  Result OnFunctionNameSubsection(Index index,
                                  uint32_t name_type,
                                  Offset subsection_size) override;
  Result OnFunctionNamesCount(Index num_functions) override;
  Result OnFunctionName(Index function_index,
                        string_view function_name) override;
  Result OnLocalNameSubsection(Index index,
                               uint32_t name_type,
                               Offset subsection_size) override;
  Result OnLocalNameFunctionCount(Index num_functions) override;
  Result OnLocalNameLocalCount(Index function_index, Index num_locals) override;
  Result OnLocalName(Index function_index,
                     Index local_index,
                     string_view local_name) override;
  Result EndNamesSection() override;

  Result BeginRelocSection(Offset size) override;
  Result OnRelocCount(Index count, Index section_index) override;
  Result OnReloc(RelocType type,
                 Offset offset,
                 Index index,
                 uint32_t addend) override;
  Result EndRelocSection() override;

  Result BeginDylinkSection(Offset size) override;
  Result OnDylinkInfo(uint32_t mem_size,
                      uint32_t mem_align,
                      uint32_t table_size,
                      uint32_t table_align) override;
  Result OnDylinkNeededCount(Index count) override;
  Result OnDylinkNeeded(string_view needed) override;
  Result EndDylinkSection() override;

  Result BeginLinkingSection(Offset size) override;
  Result OnSymbolCount(Index count) override;
  Result OnSymbol(Index sybmol_index, SymbolType type, uint32_t flags) override;
  Result OnDataSymbol(Index index,
                      uint32_t flags,
                      string_view name,
                      Index segment,
                      uint32_t offset,
                      uint32_t size) override;
  Result OnFunctionSymbol(Index index,
                          uint32_t flags,
                          string_view name,
                          Index func_index) override;
  Result OnGlobalSymbol(Index index,
                        uint32_t flags,
                        string_view name,
                        Index global_index) override;
  Result OnSectionSymbol(Index index,
                         uint32_t flags,
                         Index section_index) override;
  Result OnEventSymbol(Index index,
                       uint32_t flags,
                       string_view name,
                       Index event_index) override;
  Result OnSegmentInfoCount(Index count) override;
  Result OnSegmentInfo(Index index,
                       string_view name,
                       uint32_t alignment,
                       uint32_t flags) override;
  Result OnInitFunctionCount(Index count) override;
  Result OnInitFunction(uint32_t priority, Index function_index) override;
  Result OnComdatCount(Index count) override;
  Result OnComdatBegin(string_view name, uint32_t flags, Index count) override;
  Result OnComdatEntry(ComdatType kind, Index index) override;
  Result EndLinkingSection() override;

  Result BeginEventSection(Offset size) override;
  Result OnEventCount(Index count) override;
  Result OnEventType(Index index, Index sig_index) override;
  Result EndEventSection() override;

  Result OnInitExprF32ConstExpr(Index index, uint32_t value) override;
  Result OnInitExprF64ConstExpr(Index index, uint64_t value) override;
  Result OnInitExprV128ConstExpr(Index index, v128 value) override;
  Result OnInitExprGlobalGetExpr(Index index, Index global_index) override;
  Result OnInitExprI32ConstExpr(Index index, uint32_t value) override;
  Result OnInitExprI64ConstExpr(Index index, uint64_t value) override;

 private:
  void Indent();
  void Dedent();
  void WriteIndent();
  void LogType(Type type);
  void LogTypes(Index type_count, Type* types);
  void LogTypes(TypeVector& types);

  Stream* stream_;
  BinaryReaderDelegate* reader_;
  int indent_;
};

}  // namespace wabt

#endif  // WABT_BINARY_READER_LOGGING_H_
