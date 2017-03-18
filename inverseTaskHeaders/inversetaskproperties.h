#ifndef INVERSETASKPROPERTIES_H
#define INVERSETASKPROPERTIES_H

struct InverseTaskProperties {
    // начальное значение альфы
    double alpha;

    // начальное значение гаммы
    double gamma;

    // процент, на который допустимо изменение
    // функционала от исходной величины
    double percentage;

    // величина, на которую увеличиваем гамму
    double gammaStep;
};

#endif // INVERSETASKPROPERTIES_H
