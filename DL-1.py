import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn import datasets
boston = datasets.load_boston()
boston.data.shape

boston.feature_names

data = pd.DataFrame(boston.data)
data.columns = boston.feature_names
data

boston.target.shape

data['Price'] = boston.target
data.head()

data.describe()

data.info()

x = boston.data
y = boston.target

#splitting data
from sklearn.model_selection import train_test_split
xtrain, xtest, ytrain, ytest = train_test_split(x, y, test_size = 0.2, random_state = 50)

#Fitting Muletilinear regression t traing model
from sklearn.linear_model import LinearRegression
regressor = LinearRegression()
regressor.fit(xtrain, ytrain)

#predicting test results
y_pred = regressor.predict(xtest)

#plotting  scatter graph to show prediction
plt.scatter(ytest, y_pred, c = 'green')
plt.xlabel("Price: in $1000's")
plt.ylabel("Predicted Value")
plt.title("True value vs predicted value: Linear Regression")
plt.show()


from sklearn.metrics import mean_squared_error, mean_absolute_error
mse = mean_squared_error(ytest,y_pred)
mae = mean_absolute_error(ytest,y_pred)

print("Mean Squared Error: ", mse)
print("Mean Absolute Error: ", mae)
