#include <stdio.h>

int main() {
    FILE *file = fopen("test.csv", "w");
    if (file == NULL) {
        printf("Failed to open file.");
        return 1;
    }
    fprintf(file, "Month,TOTAL\n");
    double initial_amount = 0;
    double amount = initial_amount;
    double inflated_amount = amount;
    double monthly_increase = 1.05;
    double monthly_addition = 0.00;
    int months = 12;
    int years = months/12;
    double yearly_inflation = 1.00;

    for (int i = 1; i <= months; i++) {
        amount *= monthly_increase;
        if ((i % 12) == 0)
        {
            inflated_amount = amount;
            inflated_amount /= yearly_inflation;
        }
        fprintf(file, "%d,%.2f\n", i, amount);
        amount += monthly_addition;
    }
    fprintf(file, "\n");
    double total_contributions = monthly_addition * months;
    double initial_investment = initial_amount + total_contributions;
    double profit_percentage = ((amount - initial_investment) / initial_investment) * 100;
    fprintf(file, "Initial investments:$%.2f\n\n", initial_investment);
    fprintf(file, "Profit percentage after %d months: %.2f%%\n\n", months, profit_percentage);
    fprintf(file, "Adjusted for inflation after %.2f years: $%.2f\n\n", years, inflated_amount);
    profit_percentage = ((inflated_amount - initial_investment) / initial_investment) * 100;
    fprintf(file, "Total Value Growth: %.2f%%\n", profit_percentage);
    fclose(file);
    return 0;
}
