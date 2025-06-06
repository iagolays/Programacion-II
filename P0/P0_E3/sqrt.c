double absoluto(double n) {
    //return (n < 0) ? n : n; ao valor absoluto podeselle asar valores tanto negativos como positivos
    return (n < 0) ? -n : n;
}

//double sqrt(int numero) { //Método de Newton (aproximación); numero tratase dun double e non dun int
double sqrt(double numero) {
    double margen = 0.000001;
    double estimacion = 1.0;
    // Mientras haya una diferencia notable.
    // Es decir, que el cuadrado de nuestra estimación difiera mucho del número
    while (absoluto((estimacion * estimacion) - numero) >= margen)
    {
        double cociente = numero / estimacion;
        double promedio = (cociente + estimacion) / 2.0;
        estimacion = promedio;
    }
    return estimacion;
}

