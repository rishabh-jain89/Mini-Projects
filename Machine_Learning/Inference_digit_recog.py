import numpy as np
import pandas as pd

def load_data():
    data = pd.read_csv("./mnist_test.csv")
    label = data['label']
    new_data = data.drop('label',axis = 1).values.T
    return new_data,label

def Relu(arr):
    return np.maximum(0,arr)

def softmax(arr):
    arr_exp = np.exp(arr- np.max(arr, axis=0))  
    return arr_exp / np.sum(arr_exp, axis=0)

def forward_prop(A0,W1,B1,W2,B2):
    Z1 = W1 @ A0 + B1

    A1 = Relu(Z1)

    Z2 = W2 @ A1 + B2

    A2 = softmax(Z2)

    return A2

def inference(x, W1, B1, W2, B2):
    A2 = forward_prop(x,W1,B1,W2,B2)
    predicted = np.argmax(A2, axis = 0)
    return predicted

def accuracy(predictions, labels):
    correct = np.sum(predictions == labels)
    total = len(labels)
    print(f"Correct Predictions: {correct} / {total}")
    return (correct, total)

def main():
    print('hello')
    W1 = np.load('W1.npy')
    B1 = np.load('B1.npy')
    W2 = np.load('W2.npy')
    B2 = np.load('B2.npy')
    data, label = load_data()
    label = label.values
    prediction = inference(data,W1,B1,W2,B2 )
    (correct, total) = accuracy(prediction, label)
    print("Accuracy:", correct,"/",total)

if __name__ == "__main__":
    main()
