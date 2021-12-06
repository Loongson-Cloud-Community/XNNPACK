#include <cstdint>

namespace xnnpack {
namespace aarch32 {
struct CoreRegister {
  uint8_t code;
};

constexpr CoreRegister r0{0};
constexpr CoreRegister r1{1};
constexpr CoreRegister r2{2};
constexpr CoreRegister r3{3};
constexpr CoreRegister r4{4};
constexpr CoreRegister r5{5};
constexpr CoreRegister r6{6};
constexpr CoreRegister r7{7};
constexpr CoreRegister r8{8};
constexpr CoreRegister r9{9};
constexpr CoreRegister r10{10};
constexpr CoreRegister r11{11};
constexpr CoreRegister r12{12};
constexpr CoreRegister r13{13};
constexpr CoreRegister r14{14};
constexpr CoreRegister r15{15};
constexpr CoreRegister sp = r13;
constexpr CoreRegister lr = r14;
constexpr CoreRegister pc = r15;

// Conditional execution, only support AL (always) for now.
enum Condition : uint32_t {
  kAL = 0xe0000000,
};

enum class Error {
  kNoError,
  kOutOfMemory,
};

// A simple AAarch32 assembler.
// Right now it allocates its own memory (using `new`) to write code into (for
// testing), but will be updated to be more customizable.
class Assembler {
 public:
  explicit Assembler();
  ~Assembler();

  Assembler& add(CoreRegister Rd, CoreRegister Rn, CoreRegister Rm);

  // Reset the assembler state (no memory is freed).
  void reset();

  // Get a pointer to the start of code buffer.
  const uint32_t* const start() { return buffer_; }

 private:
  // Emits a 32-bit value to the code buffer.
  Assembler& emit32(uint32_t value);

  // Pointer to start of code buffer.
  uint32_t* buffer_;
  // Pointer to current place in code buffer.
  uint32_t* cursor_;
  // Pointer to out-of-bounds of code buffer.
  uint32_t* top_;
  // Errors encountered while assembling code.
  Error error_;
};
}  // namespace aarch32
}  // namespace xnnpack
