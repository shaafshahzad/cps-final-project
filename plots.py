import pandas as pd
import matplotlib.pyplot as plt

# plotting the line graph for yearly statistics by province
df_yearly = pd.read_csv('plot1.data', delim_whitespace=True)

plt.figure(figsize=(12, 7))

for column in df_yearly.columns[1:]:
    plt.plot(df_yearly['Year'], df_yearly[column], marker='o', linestyle='-', label=column)

plt.title('Yearly Statistics by Province')
plt.xlabel('Year')
plt.ylabel('Statistics')
plt.xticks(df_yearly['Year'])
plt.legend()
plt.grid(True)
plt.tight_layout()

# plotting the bar chart for Canada age group statistics
df_age_group = pd.read_csv('plot2.data', delim_whitespace=True, header=0, names=['AgeGroup', 'Canada'])

plt.figure(figsize=(10, 6))
plt.bar(df_age_group['AgeGroup'], df_age_group['Canada'], color=['blue', 'orange', 'green'])

plt.title('Canada Age Group Statistics')
plt.xlabel('Age Group')
plt.ylabel('Statistics')
plt.tight_layout()

plt.show()
