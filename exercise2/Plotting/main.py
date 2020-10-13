import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

values_pollingbased = [16.5, 29.4, 42.1, 54.5, 66.5, 78.2, 79.7, 79.7]

values_interruptbased = [13.2, 26.0, 38.8, 51.4, 63.5, 75.2, 79.7, 79.7]

values_avragebtn_pollingbased = [3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8]

values_avragebtn_interuptbased = [82.4, 159.4, 233.0, 301.2, 369.0, 430.2, 492.2, 550.0]

values_interruptbased_coin_sound = [1.5, 1.5, 1.5, 1.9, 1.9, 1.5, 1.5, 1.5]
values_pollingbased_coin_sound = [4.2, 4.2, 4.2, 4.8, 4.8, 4.2, 4.2, 4.2]

values_interruptbased_long = [1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 1.5, 2.0, 1.9, 1.9, 1.9, 2.0, 1.9, 1.9, 2.1, 1.9, 1.9, 1.9, 2.0, 1.9]
values_pollingbased_long = [4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.2, 4.9, 4.8, 4.8, 4.8, 4.8, 4.8, 4.8, 4.8, 4.8, 4.8, 4.8, 4.8, 4.8]



t = np.arange(1., 21., 1)
p = np.arange(1., 9., 1)


plt.title('Electricity used while playing the first part off our long song')
blue_patch = mpatches.Patch(color='blue', label='Polling based')
orange_patch = mpatches.Patch(color='orange', label='Interrupt based')
plt.legend(handles=[blue_patch, orange_patch])
plt.plot(t,  values_pollingbased_long, t, values_interruptbased_long)
plt.ylabel('µ Amper')
plt.show()



plt.title('Electricity used while playing our gaining points tune')
blue_patch = mpatches.Patch(color='blue', label='Polling based')
orange_patch = mpatches.Patch(color='orange', label='Interrupt based')
plt.legend(handles=[blue_patch, orange_patch])
plt.plot(p,  values_pollingbased_coin_sound, p, values_interruptbased_coin_sound)
plt.ylabel('µ Amper')
plt.show()





def main():
    print("Ploting")

if __name__ == "__main__":
    main()
