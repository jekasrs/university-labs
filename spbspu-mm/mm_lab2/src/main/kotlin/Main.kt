import java.lang.Math.exp
import java.lang.Math.pow
import java.util.*
import kotlin.math.pow

fun testConstant() {
    val RL = 1.0
    val RR = 5.0
    val T = 5.0
    val Xi2 = 2.0

    val u: (Double, Double) -> Double = { r, t -> 1.0 }
    val k: (Double, Double) -> Double = { r, t -> 1.0 }
    val q: (Double, Double) -> Double = { r, t -> 1.0 }
    val fi: (Double) -> Double = { r -> 1.0 }

    val f: (Double, Double) -> Double = { r, t -> 1.0 }
    val nu1: (Double) -> Double = { t -> 0.0 }
    val nu2: (Double) -> Double = { t -> 2.0 }

    val N = listOf(4, 8, 16, 32)
    val M = listOf(1000, 2000, 4000, 8000, 10000)
    println("Явный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.explicitEuler()
            print("($n;$m) "); solver.printEps()
        }
    }
    println("\nНеявный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.implicitEuler()
            print("($n;$m) "); solver.printEps()
        }
    }
}

fun testR() {
    val RL = 1.0
    val RR = 5.0
    val T = 5.0
    val Xi2 = 2.0

    val u: (Double, Double) -> Double = { r, t -> r * r }
    val k: (Double, Double) -> Double = { r, t -> 2.0 * r }
    val q: (Double, Double) -> Double = { r, t -> r + 1.0 }
    val fi: (Double) -> Double = { r -> r * r }

    val f: (Double, Double) -> Double = { r, t -> r * r * r + r * r - 12.0 * r }
    val nu1: (Double) -> Double = { t -> 1.0 }
    val nu2: (Double) -> Double = { t -> 150.0 }

    val N = listOf(4, 8, 16, 32)
    val M = listOf(1000, 2000, 4000, 8000, 10000)
    println("Явный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.explicitEuler()
            print("$n : $m "); solver.printEps()
        }
    }
    println("\nНеявный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.implicitEuler()
            print("$n : $m "); solver.printEps()
        }
    }
}

fun testT() {
    val RL = 1.0
    val RR = 5.0
    val T = 5.0
    val Xi2 = 2.0

    val u: (Double, Double) -> Double = { r, t -> Math.E.pow(-t) }
    val k: (Double, Double) -> Double = { r, t -> Math.E.pow(-t) }
    val q: (Double, Double) -> Double = { r, t -> Math.E.pow(-t) }
    val fi: (Double) -> Double = { r -> 1.0 }

    val f: (Double, Double) -> Double = { r, t -> Math.E.pow(-t*2.0) - Math.E.pow(-t)}
    val nu1: (Double) -> Double = { t -> Math.E.pow(-t) }
    val nu2: (Double) -> Double = { t -> 2.0*Math.E.pow(-t) }

    val N = listOf(4, 8, 16, 32)
    val M = listOf(1000, 2000, 4000, 8000, 10000)
    println("Явный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.explicitEuler()
            print("$n : $m "); solver.printEps()
        }
    }
    println("\nНеявный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.implicitEuler()
            print("$n : $m "); solver.printEps()
        }
    }
}

fun testRT() {
    val RL = 1.0
    val RR = 5.0
    val T = 5.0
    val Xi2 = 2.0

    val u: (Double, Double) -> Double = { r, t -> r*Math.E.pow(-t) }
    val k: (Double, Double) -> Double = { r, t -> 10.0*Math.E.pow(-t) }
    val q: (Double, Double) -> Double = { r, t -> 10.0*r*Math.E.pow(-t) }
    val fi: (Double) -> Double = { r -> r }

    val f: (Double, Double) -> Double = { r, t -> 10.0*Math.E.pow(-t*2.0)*(r*r - 1/r) - r*Math.E.pow(-t)  }
    val nu1: (Double) -> Double = { t -> Math.E.pow(-t) }
    val nu2: (Double) -> Double = { t -> 10.0*Math.E.pow(-t*2.0) + 10.0*Math.E.pow(-t) }

    val N = listOf(4, 8, 16, 32)
    val M = listOf(1000, 2000, 4000, 8000, 10000)
    println("Явный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.explicitEuler()
            print("$n : $m "); solver.printEps()
        }
    }
    println("\nНеявный метод")
    for (n in N) {
        for (m in M) {
            val solver = Solver(n, m, RL, RR, T, Xi2)
            solver.init(u, k, q, fi, f, nu1, nu2)

            solver.implicitEuler()
            print("$n : $m "); solver.printEps()
        }
    }
}

fun main(){
    println("Константный тест")
    testConstant()
//    println("Нелинейный тест по r")
//    testR()
//    println("Тест по t")
//    testT()
//    println("Тест с зависимость по r и t")
//    testRT()
}

