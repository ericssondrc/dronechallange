package szoftverhurkak


class Instruction(val channel1: Int, val channel2: Int, val channel3: Int, val channel4: Int, val time: Int) {
    override fun toString(): String = "$channel1;$channel2;$channel3;$channel4;$time"
}

interface InstructionCompiler {
    fun compile(instruction: Instruction): String
    fun compile(instructions: List<Instruction>): String
}

class SemicolonPipeInstructionCompiler : InstructionCompiler {
    override fun compile(instruction: Instruction): String {
        return instruction.toString()
    }

    override fun compile(instructions: List<Instruction>): String {
        return instructions.joinToString("|")
    }
}