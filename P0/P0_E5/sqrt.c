double absoluto(double n) {
    return (n < 0) ? -n : n; //debemos cambiar return (n < 0) ? n : n por return (n < 0) ? -n : n, para que nos de o valor absoluto se n é negativo 
}

double sqrt(double numero) { //Método de Newton (aproximación), debemos cambiar int numero por double numero, xa que pode ser un real e non necesariamente un enteiro
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

