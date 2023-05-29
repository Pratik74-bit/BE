from keras.datasets import imdb
from keras.datasets import imdb
# Load the data, keeping only 10,000 of the most frequently occuring words
(train_data, train_labels), (test_data, test_labels) = imdb.load_data(num_words = 100)

# Check the first review
train_data[0]

# Check the first label
train_labels[0]

# Since we restricted ourselves to the top 10000 frequent words, no word index should 
# we'll verify this below
# Here is a list of maximum indexes in every review --- we search the maximum index in
print(type([max(sequence) for sequence in train_data]))
# Find the maximum of all max indexes
max([max(sequence) for sequence in train_data])


# Let's quickly decode a review
# step 1: load the dictionary mappings from word to integer index
word_index = imdb.get_word_index()
# step 2: reverse word index to map integer indexes to their respective words
reverse_word_index = dict([(value, key) for (key, value) in word_index.items()])
# Step 3: decode the review, mapping integer indices to words
#
# indices are off by 3 because 0, 1, and 2 are reserverd indices for "padding", "Star
decoded_review = ' '.join([reverse_word_index.get(i-3, '?') for i in train_data[0]])
decoded_review


len(reverse_word_index)

import numpy as np
def vectorize_sequences(sequences, dimension=10000):
 results = np.zeros((len(sequences), dimension)) # Creates an all zero matrix of
 for i,sequence in enumerate(sequences):
 results[i,sequence] = 1 # Sets specific indices of resu
 return results
# Vectorize training Data
X_train = vectorize_sequences(train_data)
# Vectorize testing Data
X_test = vectorize_sequences(test_data)


X_train[0]

X_train.shape

y_train = np.asarray(train_labels).astype('float32')
y_test = np.asarray(test_labels).astype('float32')

from keras import models
from keras import layers
model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(10000,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))


from keras import models
from keras import layers
model = models.Sequential()
model.add(layers.Dense(16, activation='relu', input_shape=(10000,)))
model.add(layers.Dense(16, activation='relu'))
model.add(layers.Dense(1, activation='sigmoid'))

# Input for Validation
X_val = X_train[:10000]
partial_X_train = X_train[10000:]
# Labels for validation
y_val = y_train[:10000]
partial_y_train = y_train[10000:]

history = model.fit(partial_X_train,
 partial_y_train,
epochs=20,
batch_size=512,
validation_data=(X_val, y_val))
history = model.fit(partial_X_train,
 partial_y_train,
epochs=20,
batch_size=512,
validation_data=(X_val, y_val))

history = model.fit(partial_X_train,
 partial_y_train,
epochs=20,
batch_size=512,
validation_data=(X_val, y_val))

# Plotting losses
loss_values = history_dict['loss']
val_loss_values = history_dict['val_loss']
epochs = range(1, len(loss_values) + 1)
plt.plot(epochs, loss_values, 'bo', label="Training Loss")
plt.plot(epochs, val_loss_values, 'b', label="Validation Loss")
plt.title('Training and Validation Loss')
plt.xlabel('Epochs')
plt.ylabel('Loss Value')
plt.legend()
plt.show()


# Training and Validation Accuracy
acc_values = history_dict['binary_accuracy']
val_acc_values = history_dict['val_binary_accuracy']
epochs = range(1, len(loss_values) + 1)
plt.plot(epochs, acc_values, 'ro', label="Training Accuracy")
plt.plot(epochs, val_acc_values, 'r', label="Validation Accuracy")
plt.title('Training and Validation Accuraccy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.show()


model.fit(partial_X_train,
 partial_y_train,
epochs=3,
batch_size=512,
validation_data=(X_val, y_val))

# Making Predictions for testing data
np.set_printoptions(suppress=True)
result = model.predict(X_test)
result

# Making Predictions for testing data
np.set_printoptions(suppress=True)
result = model.predict(X_test)

from sklearn.metrics import mean_absolute_error
mae = mean_absolute_error(y_pred, y_test)
mae
