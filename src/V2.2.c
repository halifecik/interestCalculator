#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char currency[255];

void getUserInputs(double *initial_amount, double *monthly_addition, double *monthly_increase_percent,
                   double *yearly_inflation_percent, int *term_months, char *filename) {
    printf("Currency    ($/₺/€): ");
    scanf("%s", currency);
    printf("--------------------------------------------\n");
    printf("\033[1;31mUse numbers only. For decimals use '.' dots.\033[0m\n\n");
    printf("Examples: 3.12351 | 61340983 | 13.0865213412\n");
    printf("--------------------------------------------\n\n");
    printf("Investment Capital (%s): ", currency);
    scanf("%lf", initial_amount);
    printf("Monthly Addition   (%s): ", currency);
    scanf("%lf", monthly_addition);
    printf("Monthly Interest Rate (%%): ");
    scanf("%lf", monthly_increase_percent);
    printf("Yearly Inflation Rate (%%): ");
    scanf("%lf", yearly_inflation_percent);
    printf("Term (Months): ");
    scanf("%d", term_months);
    printf("--------------------------------------------\n");
    printf("\033[1;31mYou may use any ASCII equilevent characters.\033[0m\n");
    printf("--------------------------------------------\n\n");
    printf("File Name (w/o Extentions): ");
    scanf("%255s", filename);
}

char *parseNumbers(double num) {
    static char buffer[64];
    char tmp[64];
    sprintf(tmp, "%.2f", num);

    char *decimal_point = strchr(tmp, '.');
    int int_part_len = decimal_point - tmp;
    int commas = (int_part_len - 1) / 3;

    char *src = tmp + int_part_len - 1;
    char *dest = buffer + sizeof(buffer) - 1;
    *dest-- = '\0';

    for (int i = strlen(tmp) - 1; i >= int_part_len; i--) {
        *dest-- = tmp[i];
    }

    int count = 0;
    for (int i = int_part_len - 1; i >= 0; i--) {
        if (count && count % 3 == 0) {
            *dest-- = ',';
        }
        *dest-- = tmp[i];
        count++;
    }
    return dest + 1;
}


char *concatExt(const char *base, const char *ext) {
    size_t len = strlen(base) + strlen(ext) + 1;
    char *result = malloc(len);
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, base);
    strcat(result, ext);
    return result;
}

int main() {
    double initial_amount, monthly_addition, monthly_increase_percent, yearly_inflation_percent;
    char filename_base[256];
    int term_months;

    getUserInputs(&initial_amount, &monthly_addition, &monthly_increase_percent,
                  &yearly_inflation_percent, &term_months, filename_base);

    double monthly_increase = monthly_increase_percent / 100.0;
    double yearly_inflation = yearly_inflation_percent / 100.0;
    double monthly_inflation = pow(1 + yearly_inflation, 1.0 / 12.0) - 1;

    char *data_filename = concatExt(filename_base, ".csv");

    FILE *data_file = fopen(data_filename, "w");
    if (!data_file) {
        perror("Error opening data file");
        free(data_filename);
        return 1;
    }

    fprintf(data_file, "Month,Amount,Inflated,Amount_Final\n");

    double amount = initial_amount;
    double inflation_adjusted_amount = initial_amount;

    for (int month = 1; month <= term_months; month++) {
        amount = amount * (1 + monthly_increase) + monthly_addition;
        inflation_adjusted_amount = inflation_adjusted_amount * (1 + monthly_increase) + monthly_addition;
        inflation_adjusted_amount /= (1 + monthly_inflation);
        fprintf(data_file, "%d,%.2f,%.2f,\"%s    %s\"\n", month, amount, inflation_adjusted_amount, currency,
                parseNumbers(amount));
    }
    fclose(data_file);

    char *png_filename = concatExt(filename_base, "_chart.png");

    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (!gnuplot) {
        perror("Error starting gnuplot.");
        free(data_filename);
        free(png_filename);
    return 1;
    }

    fprintf(gnuplot, "set datafile separator ','\n");
    fprintf(gnuplot, "set terminal pngcairo size 800,600\n");
    fprintf(gnuplot, "set output '%s'\n", png_filename);
    fprintf(gnuplot, "set title 'Investment Growth'\n");
    fprintf(gnuplot, "set xlabel 'Month'\n");
    fprintf(gnuplot, "set ylabel 'Value (%s)'\n", currency);
    fprintf(gnuplot, "plot '%s' using 1:2 with lines title 'Value', \\\n", data_filename);
    fprintf(gnuplot, "     '%s' using 1:3 with lines title 'Inflation Adjusted'\n", data_filename);
    pclose(gnuplot);

    free(data_filename);
    free(png_filename);

    printf("\033[1;32mCalculation complete.\033[0m\n");
    printf("\033[1;33m-------------------------------");
    printf("\nData in: %s.csv\nChart in: %s_char.png\n", filename_base, filename_base);
    printf("-------------------------------");

    return 0;
}