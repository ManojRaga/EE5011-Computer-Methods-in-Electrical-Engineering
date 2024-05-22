import os
import numpy as np
import matplotlib.pyplot as plt

# Compile and run the C program
os.system("gcc -o interpolation interpolation.c -lm")  # Compile the C program
os.system("interpolation")  # Run the compiled C program

# Load data from output.txt
data = np.loadtxt("output.txt")

# Extract x and interpolated values
x_values = data[:, 0]
interpolated_values = data[:, 1]

# Calculate the exact function sin(x)
exact_values = np.sin(x_values)

# Calculate the error between interpolated and exact function
error = interpolated_values - exact_values

# Plotting
plt.figure(figsize=(16, 9))

# Plot interpolated and exact values
plt.subplot(2, 1, 1)
plt.plot(x_values, interpolated_values, 'r', label='Interpolated (Dotted)', marker=".", markersize=10)
plt.plot(x_values, exact_values, 'b', label='Exact (sin(x))', linewidth=2)
plt.legend()
plt.title("Interpolated vs. Exact Function Sin(x)")
plt.xlabel("x")
plt.ylabel("y")

# Plot the error
plt.subplot(2, 1, 2)
plt.plot(x_values, error, 'g', label='Error', linewidth=2)
plt.legend()
plt.title("Error b/w Lagrange Interpolation and Exact Sin(x)")
plt.xlabel("x")
plt.ylabel("Error")

plt.tight_layout()
plt.show()