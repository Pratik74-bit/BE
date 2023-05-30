import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM

# Step 1: Import the required libraries

# Step 2: Load the dataset
data = pd.read_csv('google_stock_prices.csv')

# Step 3: Preprocess the data
prices = data['Close'].values.reshape(-1, 1)
scaler = MinMaxScaler(feature_range=(0, 1))
scaled_prices = scaler.fit_transform(prices)

# Step 4: Split the data into training and testing sets
train_size = int(len(scaled_prices) * 0.8)
train_data = scaled_prices[:train_size]
test_data = scaled_prices[train_size:]

# Step 5: Prepare the data for training the RNN
def create_sequences(data, seq_length):
    x = []
    y = []
    for i in range(len(data) - seq_length):
        x.append(data[i:i+seq_length])
        y.append(data[i+seq_length])
    return np.array(x), np.array(y)

sequence_length = 20
x_train, y_train = create_sequences(train_data, sequence_length)
x_test, y_test = create_sequences(test_data, sequence_length)

x_train = np.reshape(x_train, (x_train.shape[0], x_train.shape[1], 1))
x_test = np.reshape(x_test, (x_test.shape[0], x_test.shape[1], 1))

# Step 6: Build the RNN model
model = Sequential()
model.add(LSTM(50, return_sequences=True, input_shape=(sequence_length, 1)))
model.add(LSTM(50, return_sequences=False))
model.add(Dense(1))

model.compile(optimizer='adam', loss='mean_squared_error')

# Step 7: Train the model
model.fit(x_train, y_train, epochs=50, batch_size=32)

# Step 8: Predict the stock prices using the trained model
predictions = model.predict(x_test)
predicted_prices = scaler.inverse_transform(predictions)

# Step 9: Evaluate the model
rmse = np.sqrt(np.mean((predicted_prices - scaler.inverse_transform(y_test))**2))
print('Root Mean Squared Error (RMSE):', rmse)
