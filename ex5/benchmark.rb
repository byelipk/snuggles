require "benchmark"

n = 1_000_000

Benchmark.bm() do |x|
	x.report("Multiplication:") {  1.upto(n) { 8 * (2 ** 2) } } # 32
	x.report("Bitwise <<:    ") {  1.upto(n) { 8 << 2 } }       # 32
end

Benchmark.bm() do |x|
	x.report("Integer Division:") {  1.upto(n) { 10 / 2  } } # 5
	x.report("Bitwise >>:      ") {  1.upto(n) { 10 >> 1 } } # 5
end
