
class Solver (var N: Int, val M:Int, val RL: Double, val RR: Double, T: Double, val Xi2: Double) {
    val a: Array<Double> = Array(N-1) { 0.0 }
    val b: Array<Double> = Array(N-1) { 0.0 }
    val c: Array<Double> = Array(N-1) { 0.0 }
    var d: Array<Double> = Array(N-1) { 0.0 }

    var v: Array<Array<Double>> = Array(N) { Array(M+1) {0.0} }
    var U: Array<Array<Double>> = Array(N) { Array(M+1) {0.0} }
    var g: Array<Double> = Array(N) { 0.0 }

    private val h:Double = (RR - RL)/N
    private val h_h:Double = h/2
    val tay: Double = T / M

    private val t: Array<Double> = Array(M+1){0.0}
    val r: Array<Double> = Array(N+1){0.0}
    private val r_h: Array<Double> = Array(N+1){0.0}

    lateinit var u: ((Double, Double) -> Double)
    lateinit var k: ((Double, Double) -> Double)
    lateinit var q: ((Double, Double) -> Double)
    lateinit var fi: ((Double) -> Double)

    lateinit var f: ((Double, Double) -> Double)
    lateinit var nu1: ((Double) -> Double)
    lateinit var nu2: ((Double) -> Double)

    /**
     * Заполняет значения векторов r и h, t для основной сетки и вспомогательной.
     *
     * Массивы r и h нужны для ИИМ (интегро-интерполяционного метода)
     */
    private fun initNet() {
        // основная сетка h
        for (i in 0 .. N)
            r[i] = RL + i*h

        // вспомогательная сетка
        r_h[0] = 0.0
        for (i in 1 .. N)
            r_h[i] = (r[i] + r[i - 1]) / 2.0

        // основная сетка t
        for (i in 0..M)
            t[i] = 0.0 + i*tay
    }

    /**
     * Заполняет матрицы А и D и вектор g.
     */
    private fun initMatrix(time: Double, method: Int) {
        b[0] = ((r_h[2] * k(r_h[2], time)) / h)
        c[0] = - (r_h[1] * k(r_h[1], time)) / h - (r_h[2] * k(r_h[2], time)) / h - h_h*r[1]*q(r[1], time)
        d[0] = 1.0 / (h_h * r[1])
        g[0] = nu1(time) * (r_h[1] * k(r_h[1], time)) / h + h_h * r[1] * f(r[1], time)

        // основная часть СЛАУ
        for (i in 1 until N - 1) {
            a[i] = ((r_h[i+1] * k(r_h[i+1], time)) / h)
            c[i] = ( -(r_h[i+1] * k(r_h[i+1], time))/h - (r_h[i + 2] * k(r_h[i + 2], time))/h - h_h * r[i+1] * q(r[i+1], time))
            b[i] = ((r_h[i + 2] * k(r_h[i + 2], time)) / h)
            g[i] = h_h * r[i+1] * f(r[i+ 1], time)
            d[i] = 1.0 / (h_h * r[i+1])
        }

        // граничное условие справа - последняя строчка СЛАУ
        a[N - 1] = ((r_h[N] * k(r[N], time)) / h)
        c[N - 1] = (-(r_h[N] * k(r[N], time)) / h - (h / 2.0) * r[N] * q(r[N], time) - r[N] * Xi2)
        g[N - 1] = (h / 2.0) * r[N] * f(r[N], time) + r[N] * nu2(time)
        d[N - 1] = 2.0 / ((h) * r[N])

        if (method == 1) {
            // Приводим векторы a, b, c, g к форме записи с Ãv + ġ
            for (i in 0 until N) {
                if (i != 0) a[i] = a[i] * d[i]
                c[i] = c[i] * d[i]
                b[i] = b[i] * d[i]
                g[i] = g[i] * d[i]

                if (i != 0) a[i] *= tay
                c[i] = c[i] * tay + 1.0
                b[i] *= tay
                g[i] *= tay
            }
        }
        if (method == 2) {
            // Приводим векторы a, b, c, g к форме записи с Ãv + ġ
            for (i in 0 until N) {
                if (i != 0) a[i] = a[i] * d[i]
                c[i] = c[i] * d[i]
                b[i] = b[i] * d[i]
                g[i] = g[i] * d[i]

                if (i != 0) a[i] *= -tay
                c[i] = 1.0 - c[i] * tay
                b[i] *= -tay
                g[i] *= tay
            }
        }
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
    fun progonka(aV: Array<Double>, cV: Array<Double>, bV: Array<Double>, gV: Array<Double>, size: Int): Array<Double> {
        // прогоночные коэффициенты alpha и beta
        val alpha: Array<Double> = Array(size+1) { 0.0 }
        val beta: Array<Double> = Array(size+1) { 0.0 }
        val res: Array<Double> = Array(size+1) { 0.0 }

        // прямой ход - считаем коэффициенты alpha и beta
        alpha[1] = -bV[0] / cV[0]
        beta[1] = gV[0] / cV[0]

        for (i in 1 until size) {
            alpha[i + 1] = -(bV[i]) / (alpha[i] * aV[i] + cV[i])
            beta[i + 1] = (gV[i] - aV[i] * beta[i]) / (aV[i] * alpha[i] + cV[i])
        }

        // обратный ход - находим веткор решений v
        res[size] = ((gV[size] - aV[size] * beta[size]) / (aV[size] * alpha[size] + cV[size]))
        for (i in size-1 downTo 0 step 1) {
            res[i] = alpha[i + 1] * res[i + 1] + beta[i + 1]
        }

        return res
    }

    /** явный метод Эйлера **/
    fun explicitEuler() {
        var method = 1
        for (i in 0 until N) v[i][0] = fi(r[i])
        for (k in 1..M) {
            initMatrix(t[k-1], method)

            v[0][k] = c[0] * v[0][k - 1] + b[0] * v[1][k - 1] + g[0]
            for (i in 1 until N-1)
                v[i][k] = a[i] * v[i - 1][k - 1] + c[i] * v[i][k - 1] + b[i] * v[i + 1][k - 1] + g[i]
            v[N-1][k] = a[N-1] * v[N-2][k - 1] + c[N-1] * v[N-1][k - 1] + g[N-1]
        }
    }

    /** неявный метод Эйлера **/
    fun implicitEuler() {
        val method = 2
        for (i in 0 until N) v[i][0] = fi(r[i])
        for (k in 1 .. M) {
            initMatrix(t[k], method)

            val G = Array(N){0.0}
            for (i in 0 until N) G[i] = v[i][k-1] + g[i]

            val tmp = progonka(a, c, b, G, N-1)

            for (i in 0 until N) v[i][k] = tmp[i]
        }
    }

    fun init(u_: (Double, Double) -> Double, k_: (Double, Double) -> Double, q_: (Double, Double) -> Double, fi_: (Double) -> Double,
             f_: (Double, Double) -> Double, nu1_: (Double) -> Double, nu2_ : (Double) -> Double ) {
        u = u_
        k = k_
        q = q_
        fi = fi_

        f = f_
        nu1 = nu1_
        nu2 = nu2_

        initNet()
    }

    /**
     * Считает невязку [u-v] для каждой точки.
     * Находит максимальное отклонение по модулю, что и считается за погрешность всего решения
     */
    fun printEps() {
        for (i in 1 until N) for (k in 1..M) U[i][k] = u(r[i], t[k])

        var maxEps = -1.0
        for(i in 1 until N) for (k in 1..M)
            maxEps = kotlin.math.max(maxEps, kotlin.math.abs(U[i][k] - v[i][k]))
        println(String.format("eps = %.5e", maxEps))
    }
    companion object {
        fun printVector(v: Array<Double>, ch: Char) {
            print("$ch = ")
            v.forEach { i -> print(String.format("%2.6f; ", i)) }
            println()
        }
    }
}





