import java.util.*

val scanner = Scanner(System.`in`)

fun main() {

    print("N   = "); val N = scanner.nextInt()
    print("M   = "); val N = scanner.nextInt()
    print("RL   = "); val RL = scanner.nextDouble()
    print("RR   = "); val RR = scanner.nextDouble()
    print("v1   = "); val v1 = scanner.nextDouble()
    print("v2   = "); val v2 = scanner.nextDouble()
    print("Xi2   = "); val Xi2 = scanner.nextDouble()

    val u: (Double) -> Double = { r: Double -> r }
    val k: (Double) -> Double = { 1.0 }
    val q: (Double) -> Double = { r: Double -> 2.0 }
    val f: (Double) -> Double = { r: Double -> 2.0 * r -1.0/r}

    val solver = Solver(N, RL, RR, v1, v2, Xi2)
    solver.init(u, k, q, f)
    val v = solver.progonka()
    solver.printEps()
    Solver.printVector(solver.r, 'r')
    Solver.printVector(v, 'v')
}



fun test() {
    val n = listOf(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16000, 32000, 64000)
    for (i in n) test1(i)
    for (i in n) test2(i)
    for (i in n) test3(i)
}

fun test1(N:Int) {
    println("Test 1 N = $N")
    /* Вычислительная error constant */
    val RL = 1.0
    val RR = 11.0

    val v1 = 1.0
    val Xi2 = 2.0
    val v2 = 2.0

    val u: (Number) -> Double  = {1.0}
    val k: (Number) -> Double  = {1.0}
    val q: (Number) -> Double  = {1.0}
    val f: (Number) -> Double  = {1.0}

    val solver = Solver(N, RL, RR, v1, v2, Xi2)
    solver.init(u, k, q, f)
    solver.progonka()
    solver.printEps()
}
fun test2(N:Int) {
    /* Вычислительная error linear */
    println("Test 3 N = $N")
    val RL = 2.0
    val RR = 5.0

    val v1 = 2.0
    val Xi2 = 1.0
    val v2 = 6.0

    val u: (Double) -> Double = { r: Double -> r }
    val k: (Double) -> Double = { 1.0 }
    val q: (Double) -> Double = { r: Double -> 2.0 }
    val f: (Double) -> Double = { r: Double -> 2.0 * r -1.0/r}

    val solver = Solver(N, RL, RR, v1, v2, Xi2)
    solver.init(u, k, q, f)
    solver.progonka()
    solver.printEps()
}
fun test3(N:Int) {
    /* Approximation error General test */
    println("Test 3 N = $N")
    val RL = 2.0
    val RR = 5.0

    val v1 = 8.0
    val Xi2 = 1.0
    val v2 = 9500.0

    val u: (Double) -> Double  = { r: Double -> r*r*r }
    val k: (Double) -> Double  = { r: Double -> r*r*r }
    val q: (Double) -> Double  = { r: Double -> 2.0*r }
    val f: (Double) -> Double  = { r: Double -> -16.0*r*r*r*r}

    val solver = Solver(N, RL, RR, v1, v2, Xi2)
    solver.init(u, k, q, f)
    solver.progonka()
    solver.printEps()
}
