
Tradeoffs considered


1. Assembler is more complex while our assembly code itself becomes less complex
2. Splitting L1 cache into code + data is justified by realizing that math benchmarks will use the same instructions but different math data per instruction
3. Default signed vs unsigned memory? Is it better to use a uint_32 as default and typecast every where we need signed or the other way around?
