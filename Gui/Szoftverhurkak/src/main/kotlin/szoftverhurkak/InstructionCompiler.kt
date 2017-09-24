package szoftverhurkak


class Instruction(val channel1: Int, val channel2: Int, val channel3: Int, val channel4: Int, val time: Int) {
    override fun toString(): String = "$channel1;$channel2;$channel3;$channel4;$time"

    companion object {
        fun fromString(str: String): Instruction {
            val matched = str.split(";")
            return Instruction(
                matched.elementAt(0).toInt(),
                matched.elementAt(1).toInt(),
                matched.elementAt(2).toInt(),
                matched.elementAt(3).toInt(),
                matched.elementAt(4).toInt())
        }
    }
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