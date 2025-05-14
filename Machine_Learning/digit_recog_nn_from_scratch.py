import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

alpha = 0.001

def load_data():
    data = pd.read_csv('./mnist_train.csv')
    label = data['label']
    new_data = data.drop('label',axis = 1).values.T
    return new_data,label

def initializing_params(n):
    W1 = np.array(np.random.randn(n[1],n[0]))
    W2 = np.array(np.random.randn(n[2],n[1]))
    B1 = np.array(np.random.randn(n[1],1))
    B2 = np.array(np.random.rand(n[2],1))
    return W1,W2,B1,B2

def one_hot(label,n,m):
    labels = np.zeros((m,n[2]))
    for i in range(0,len(label)):
        labels[i][label[i]] = 1
    return labels

def Relu(arr):
    return np.maximum(0,arr)

def sigmoid(arr):
    return 1/(1+np.exp(-1 * arr))

def softmax(arr):
    arr_exp = np.exp(arr- np.max(arr, axis=0))  
    return arr_exp / np.sum(arr_exp, axis=0)

def forward_prop(A0,W1,B1,W2,B2):
    Z1 = W1 @ A0 + B1

    A1 = Relu(Z1)

    Z2 = W2 @ A1 + B2

    A2 = softmax(Z2)

    return A1,A2

def get_cost(label,predicted):
    eps = 1e-10
    predicted = np.clip(predicted, eps, 1 - eps)
    return -np.mean(np.sum(label * np.log(predicted), axis=0))

def get_accuracy(A2, label):
    predictions = np.argmax(A2, axis=0)
    true_labels = np.argmax(label, axis=0)
    acc = np.mean(predictions == true_labels)
    return acc

def backprop(data, y, A1, A2, W2, m):
    dZ2 = A2 - y
    dW2 = (1/m) * dZ2@A1.T
    dB2 = (1/m) * np.sum(dZ2, axis = 1, keepdims=True)

    dA1 = W2.T @ dZ2

    dZ1 = dA1 * (A1 > 0)
    dW1 = (1/m) * dZ1 @ data.T
    dB1 = (1/m) * np.sum(dZ1, axis = 1, keepdims=True)

    return np.array(dW1),np.array(dB1),np.array(dW2),np.array(dB2)

def show(iter, cost, acc):
    plt.plot(iter, cost)
    plt.show()

    plt.plot(iter, acc)
    plt.show()

def training(num, n, data, m, label):
    W1,W2,B1,B2 = initializing_params(n)
    cost = []
    accuracy = []
    iter = []
    for i in range(num):
        A1,A2 = forward_prop(data,W1,B1,W2,B2)
        dw1,db1,dw2,db2 = backprop(data,label,A1,A2,W2,m)
        W1 -= alpha * dw1
        B1 -= alpha * db1
        W2 -= alpha * dw2
        B2 -= alpha * db2
        if i % 10 == 0:
            iter.append(i)
            cos = get_cost(label,A2)
            acc = get_accuracy(A2,label)*100
            cost.append(cos)
            accuracy.append(acc)
            print("cost after ",i," iterations:",cos)
            print("accuracy: ",acc)
            # show(iter, cost, accuracy)
    np.save('/W1.npy', W1)
    np.save('/B1.npy', B1)
    np.save('/W2.npy', W2)
    np.save('/B2.npy', B2)

def main():
    data,label = load_data()
    label = label.values
    n = [784,128,10]
    m = label.shape[0]
    label = one_hot(label,n,m)
    label = np.transpose(label)
    training(1000, n, data, m, label)

if __name__ == "__main__":
    main()
