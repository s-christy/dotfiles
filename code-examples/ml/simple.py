from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
import numpy as np
import tensorflow as tf

#input and expected output
x = tf.constant([[1], [2], [3], [4]], dtype=tf.float32)#tensor input
y = tf.constant([[0], [-1], [-2], [-3]], dtype=tf.float32)#tensor output

#model
linear_model = tf.layers.Dense(units=1)#TODO
y_pred = linear_model(x)
loss = tf.losses.mean_squared_error(labels=y, predictions=y_pred)#loss function
optimizer = tf.train.GradientDescentOptimizer(0.01)#optimizer
train = optimizer.minimize(loss)#train may be a operation?

#initiate the training simulation
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
try:
  for i in range(1000000):
    out=sess.run((train, loss))
    if i%1000==0: print(out)
except:
  pass

#what is y_pred exactly?
print(sess.run(y_pred))#sess.run prints out the value of the tensor
print("CTRL-D to exit")



