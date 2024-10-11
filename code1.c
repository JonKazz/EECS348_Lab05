#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Removes all non pritable chars that would break float conversion
void removeNonPrintableChars(char *str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isprint((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Null-terminate the modified string
}

void sorted_sales_report(const char *months[], char *month_data[]) {
    // Array to hold the sales values and corresponding month indices
    float sales_values[12];
    int indices[12];

    // Convert month_data strings to float and populate sales_values
    for (int i = 0; i < 12; i++) {
        removeNonPrintableChars(month_data[i]); // Clean the string
        sales_values[i] = atof(month_data[i]);
        indices[i] = i; // Store the original index
    }

    // Sort the sales_values in descending order using bubble sort and keep track of the indices
    for (int i = 0; i < 12 - 1; i++) {
        for (int j = 0; j < 12 - i - 1; j++) {
            if (sales_values[j] < sales_values[j + 1]) {
                // Swap sales_values
                float temp = sales_values[j];
                sales_values[j] = sales_values[j + 1];
                sales_values[j + 1] = temp;

                // Swap indices
                int temp_index = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp_index;
            }
        }
    }

    printf("\nSales Report (Highest to Lowest):\n");
    printf("%-10s %s\n", "Month", "Sales");
    for (int i = 0; i < 12; i++) {
        printf("%-10s $%.2f\n", months[indices[i]], sales_values[i]);
    }
}


void average_moving_report(const char *months[], char *month_data[]) {
    printf("Six-Month moving average report:\n");
    removeNonPrintableChars(month_data[0]);
    for (int cycle=0; cycle<7; cycle++) {
        float sales = 0;
        for (int i=0; i<6; i++) {
            sales += atof(month_data[i+cycle]);
        }
        float average = sales / 6.0;
        printf("%-8s - %-10s $%.2f\n", months[cycle], months[cycle + 5], average);
    }
}

void monthly_sales_report(const char *months[], char *month_data[]) {
    printf("\nMonthly Sales Report:\n");
    printf("%-10s %s\n", "Month", "Sales");

    for (int i = 0; i < 12; i++)
    {
        // Print each month and its corresponding sales data
        printf("%-10s %s", months[i], month_data[i]);
    }
}

void sales_summary_report(const char *months[], char *month_data[]) {
    removeNonPrintableChars(month_data[0]);
    float maximum = atof(month_data[0]);
    float minimum = atof(month_data[0]);
    float total = 0.0;
    int max_index = 0;
    int min_index = 0;

    for (int i = 0; i < 12; i++)
    {
        float sales = atof(month_data[i]);

        total += sales;
        // Update maximum if the current sales are higher
        if (sales > maximum)
        {
            maximum = sales;
            max_index = i;
        }
        // Update minimum if the current sales are lower
        if (sales < minimum)
        {
            minimum = sales;
            min_index = i;
        }
    }

    // Calculate the average
    float average = total / 12.0;

    // Print the sales summary
    printf("\nSales summary report:\n");
    printf("Maximum Sales: $%.2f (%s)\n", maximum, months[max_index]);
    printf("Minimum Sales: $%.2f (%s)\n", minimum, months[min_index]);
    printf("Average Sales: $%.2f\n", average);
}


int main()
{
    FILE *file;
    char *month_data[12];
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    char buffer[256];
    int line_count = 0;

    // Open the file in read mode
    file = fopen("sales.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Read each line from the file and store it in the array
    while (fgets(buffer, 256, file) != NULL && line_count < 12)
    {
        // Allocate memory for each line and copy the buffer content
        month_data[line_count] = malloc(strlen(buffer) + 1);
        if (month_data[line_count] == NULL)
        {
            printf("Memory allocation error.\n");
            return 1;
        }
        strcpy(month_data[line_count], buffer);
        line_count++;
    }

    fclose(file);

    monthly_sales_report(months, month_data);
    printf("\n");
    sales_summary_report(months, month_data);
    printf("\n");
    average_moving_report(months, month_data);
    printf("\n");
    sorted_sales_report(months, month_data);

    return 0;
}