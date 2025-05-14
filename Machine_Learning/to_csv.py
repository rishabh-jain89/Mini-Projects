import struct
import numpy as np
import csv

def read_images(filename):
    with open(filename, 'rb') as f:
        magic, num, rows, cols = struct.unpack(">IIII", f.read(16))
        images = np.frombuffer(f.read(), dtype=np.uint8)
        images = images.reshape(num, rows * cols)
    return images

def read_labels(filename):
    with open(filename, 'rb') as f:
        magic, num = struct.unpack(">II", f.read(8))
        labels = np.frombuffer(f.read(), dtype=np.uint8)
    return labels

def write_csv(images, labels, filename):
    with open(filename, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['label'] + [f'pixel{i}' for i in range(784)])
        for img, label in zip(images, labels):
            writer.writerow([label] + img.tolist())

# Paths to ubyte files
image_file = '/home/rishabh-jain/Desktop/Neural Networks/archive/t10k-images.idx3-ubyte'
label_file = '/home/rishabh-jain/Desktop/Neural Networks/archive/t10k-labels.idx1-ubyte'

# Read and write
images = read_images(image_file)
labels = read_labels(label_file)
write_csv(images, labels, 'mnist_test.csv')
