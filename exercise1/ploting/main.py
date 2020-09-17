import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

values_pollingbased = [16.5, 29.4, 42.1, 54.5, 66.5, 78.2, 79.7, 79.7]

values_interruptbased = [13.2, 26.0, 38.8, 51.4, 63.5, 75.2, 79.7, 79.7]

values_avragebtn_pollingbased = [3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8]

values_avragebtn_interuptbased = [82.4, 159.4, 233.0, 301.2, 369.0, 430.2, 492.2, 550.0]


t = np.arange(1., 9., 1)
values = []
print(t)


plt.bar(t, values_avragebtn_interuptbased)
plt.show()

ax = plt.subplot(111)
blue_patch = mpatches.Patch(color='blue', label='Polling based')
red_patch = mpatches.Patch(color='red', label='Interrupt based')
plt.legend(handles=[blue_patch, red_patch])
plt.title('Electicity used when buttons pressed with LEDs')
plt.ylabel('m amper')
plt.xlabel('number of buttons pressed on controller')
ax.bar(t+0.5, values_pollingbased, width=0.5, color='r', label='Interupt', align='center')
ax.bar(t, values_interruptbased, width=0.5, color='b', label='Polling', align='center')

plt.show()
for value in values_avragebtn_pollingbased:
    values.append(value*1000)
print(values)

plt.title('Electricity used when buttons pressed without LEDs')
blue_patch = mpatches.Patch(color='blue', label='Polling based')
orange_patch = mpatches.Patch(color='orange', label='Interrupt based')
plt.legend(handles=[blue_patch, orange_patch])
plt.plot(t,  values, values_avragebtn_interuptbased)
plt.ylabel('µ amper')
plt.xlabel('number of buttons pressed on controller')
plt.show()







def main():
    print("Ploting")

if __name__ == "__main__":
    main()
