/**
 * **Организует математические вычисления в одном объекте**
 *
 * **0 шаг**
 *
 * Создается объект для системы, в конструкторе задаются параметры: [N], [RL], [RR], [v1], [v2], [Xi2]
 *
 * **1 шаг**
 *
 * Инициализируются все поля и методы, а именно:
 * * задаются функции вычисляющие k, f, u, q, k_h
 * * вызывается метод [initNet] - инициализирует параметры для основной и вспомогательной сетки
 * * вызывается метод [initMatrix] - инициализирует коэффициенты для трех-диагональной матрицы A(a, b, c) и вектор g для СЛАУ Av=g
 *
 * **2 шаг**
 *
 * Вызывается метод [progonka], который решает СЛАУ методом прогонки для трех диагональной матрицы А
 *
 * **3 шаг**
 *
 * Вызывается метод [computeErrorAndShow], считает невязку[[u]-[v]] для каждого i-ого разбиения и выбирает максимальную - погрешность всего уравнения
 *
 * @param N число разбиений > 0
 * @param RL начало промежутка > 0
 * @param RR конец промежутка
 * @param v1 первое граничное условие
 * @param v2 часть второго граничного условия
 * @param Xi2 часть второго граничного условия
 *
 * @property h веткор "шаг" основной сетки
 * @property h_h вектор "шаг" вспомогательной сетки
 * @property r
 * @property r_h
 *
 * @property k_h fun k_h(**x**: Number):Double внутренняя функция уравнений
 * **x** - аргумент функции r[[RL];[RR]]
 * @property q fun q(**x**: Number):Double внутренняя функция уравнений
 * **x** - аргумент функции r[[RL];[RR]]
 * @property u fun u(**x**: Number):Double внутренняя функция уравнений
 * **x** - аргумент функции r[[RL];[RR]]
 * @property f fun f(**x**: Number):Double внутренняя функция уравнений
 * **x** - аргумент функции r[[RL];[RR]]
 */

class Solver(var N: Int, val RL: Double, val RR: Double, val v1: Double, val v2: Double, val Xi2: Double) {
    val a: Array<Double>
    val b: Array<Double>
    val c: Array<Double>

    var v: Array<Double>
    var g: Array<Double>

    private val h: Array<Double>
    private val h_h: Array<Double>
    val r: Array<Double>
    private val r_h: Array<Double>

    lateinit var k: ((Double) -> Double)
    lateinit var q: ((Double) -> Double)
    lateinit var u: ((Double) -> Double)
    lateinit var f: ((Double) -> Double)

    init {
        if (N < 0) N = 0

        a = Array(N + 1) { 0.0 }
        b = Array(N + 1) { 0.0 }
        c = Array(N + 1) { 0.0 }

        v = Array(N + 1) { 0.0 }
        g = Array(N + 1) { 0.0 }

        h = Array(N+1){0.0}
        h_h = Array(N+1){0.0}
        r = Array(N+1){0.0}
        r_h = Array(N+1){0.0}
    }

    fun init(u_: (Double) -> Double, k_: (Double) -> Double, q_: (Double) -> Double, f_: (Double) -> Double ) {
        u = u_
        k = k_
        q = q_
        f = f_

        initNet()
        initMatrix()
    }

    /**
     * Заполняет значения векторов r и h для основной сетки и вспомогательной.
     *
     * Массивы r и h нужны для ИИМ (интегро-интерполяционного метода)
     */
    private fun initNet() {
        var step = RL
        val inc: Double = (RR - RL) / N

        // основная сетка
        r[0] = step
        for (i in 1..N) {
            step += inc
            r[i] = step
            h[i] = inc
        }

        // вспомогательная сетка
        h_h[0] = h[1]/2.0
        h_h[N] = h[N]/2.0
        r_h[N] = (r[N] + r[N - 1]) / 2.0
        for (i in 1 until N) {
            r_h[i] = (r[i] + r[i - 1]) / 2.0
            h_h[i] = (h[i] + h[i + 1]) / 2.0
        }

        println("Инициализация сетки успешна")
    }

    /**
     * Заполняет матричное уравнение Av=g: матрицу А, вектор g.
     */
    private fun initMatrix() {

        // граничное условие слева - первая строчка СЛАУ
        c[0] = 1.0
        b[0] = 0.0
        g[0] = v1

        // temp variables
        var k_m: Double  // k1/2-1
        var k_p: Double  // k1/2+1
        var r_m: Double  // r1/2-1
        var r_p: Double  // к1/2+1

        // основная часть СЛАУ
        for (i in 1 until N) {
            k_m = k(r[i]-h[i]/2)
            k_p = k(r[i]+h[i]/2)
            r_m = r_h[i]
            r_p = r_h[i+1]

            a[i] = -((r_m*k_m)/h[i])
            c[i] = ((r_m*k_m)/h[i] + (r_p*k_p)/h[i+1] + h_h[i]*r[i]*q(r[i]))
            b[i] = -((r_p*k_p)/h[i+1])
            g[i] = h_h[i]*r[i]*f(r[i])
        }

        // граничное условие справа - последняя строчка СЛАУ

        a[N] = -((r_h[N]*k(r[N]-h[N]/2))/h[N])
        c[N]  = ((r_h[N]*k(r[N]-h[N]/2))/h[N] + h_h[N]*r[N]*q(r[N]) + r[N]*Xi2);
        g[N] = h_h[N]*r[N]*f(r[N]) + r[N]*v2

        println("Инициализация матрицы А и вектора g успешны")
    }

    /**
     * Находит решение матричного уравнения Av=g методом 'прогонки' (прямой и обратный ход)
     *
     * Решение ищется в виде v(i)=α(i+1)*v(i+1)+β(i+1)
     * @param A матрица размера N*N
     * @param g вектор размера N
     *
     * @return v вектор решений
     */
    fun progonka(): Array<Double> {
        // прогоночные коэффициенты alpha и beta
        val alpha: Array<Double> = Array(g.size) { 0.0 }
        val beta: Array<Double> = Array(g.size) { 0.0 }

        // прямой ход - считаем коэффициенты alpha и beta
        alpha[1] = -b[0] / c[0]
        beta[1] = g[0] / c[0]

        for (i in 1 until N) {
            alpha[i + 1] = -(b[i]) / (alpha[i] * a[i] + c[i])
            beta[i + 1] = (g[i] - a[i] * beta[i]) / (a[i] * alpha[i] + c[i])
        }

        // обратный ход - находим веткор решений v
        v[N] = ((g[N] - a[N] * beta[N]) / (a[N] * alpha[N] + c[N]))
        for (i in N-1 downTo 0 step 1) {
            v[i] = alpha[i + 1] * v[i + 1] + beta[i + 1]
        }

        println("Расчет нахождения решения СЛАУ методом прогонки закончен")
        return v
    }

    /**
     * Считает невязку [u-v] для каждой точки.
     * Находит максимальное отклонение по модулю, что и считается за погрешность всего решения
     */
    fun printEps() {
        var maxEps= -1.0
        var eps: Double

        for(i in 0..N) {
            eps = kotlin.math.abs(u(r[i]) - v[i])
//            println("$i: u[$i]) - v[$i] = $eps")
//            println("$i: " + u(r[i]) + " - " +  v[i] + " = " + eps)
            if (eps > maxEps) {
                maxEps = eps
            }
        }
        println(String.format("eps = %.3e \n\n", maxEps))
    }

    companion object {
        fun printVector(v: Array<Double>, ch: Char) {
            print("$ch = ")
            v.forEach { i -> print(String.format("%2.6f; ", i)) }
            println()
        }
    }
}

