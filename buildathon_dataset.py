# -*- coding: utf-8 -*-
"""buildathon_dataset.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1_a1aqpRqyY7AOt1XqEw69sHntY4p1YJp

UNITS CONSUMED
"""

import numpy as np

for i in range(1,5):
  unit = np.random.normal(221.21*i, 150, 10000)
  print(i)

print(np.mean(unit))
import matplotlib.pyplot as plt
plt.hist(unit, 100)
plt.show()

len(unit)

print(unit)

"""TEMPERATURE"""

temp=[]
temp_min = np.random.normal(26, 1, 10000)
for i in range(0,len(temp_min)):
  if temp_min[i]>15 and temp_min[i]<55:
   temp_min[i]=temp_min[i]

temp_min = temp_min*(unit/886.75)
    

print(np.mean(temp_min))
import matplotlib.pyplot as plt
plt.hist(temp_min, 100)
plt.show()
np.mean(temp_min)
temp_min

temp_max = np.random.normal(32, 10, 10000)
temp_max = temp_max*(unit/886.75)

print(np.mean(temp_max))
import matplotlib.pyplot as plt
plt.hist(temp_max, 100)
plt.show()
np.mean(temp_max)

"""RAIN FALL"""

#418.94

rain = np.random.normal(418.94, 30, 10000)
rain = rain*(unit/886.75)

np.mean(rain)
import matplotlib.pyplot as plt
plt.hist(rain, 100)
plt.show()
np.mean(rain)

"""HUMIDITY"""

humidity = np.random.normal(78, 1, 10000)
humidity = humidity*(unit/886.75)
np.mean(humidity)
import matplotlib.pyplot as plt
plt.hist(humidity, 100)
plt.show()
np.mean(humidity)

"""INSTITUTION"""

inst= np.random.randint(0, high=5, size=10000)
print(inst)

from google.colab import auth
auth.authenticate_user()

import gspread
from google.auth import default
creds, _ = default()

gc = gspread.authorize(creds)

# sh = gc.create('test1')

# Open our new sheet and add some data.
worksheet = gc.open('test1').sheet1

cell_list = worksheet.range('A2:A10001')
i=0
 
for cell in cell_list:
  cell.value = round(unit[i],2)
  i=i+1

worksheet.update_cells(cell_list)

######################################################################
cell_list = worksheet.range('B2:B10001')
i=0
 
for cell in cell_list:
  cell.value = round(temp_min[i],2)
  i=i+1

worksheet.update_cells(cell_list)

######################################################################
cell_list = worksheet.range('C2:C10001')
i=0
 
for cell in cell_list:
  cell.value = round(temp_max[i],2)
  i=i+1

worksheet.update_cells(cell_list)

######################################################################
cell_list = worksheet.range('D2:D10001')
i=0
 
for cell in cell_list:
  cell.value = round(humidity[i],2)
  i=i+1

worksheet.update_cells(cell_list)

######################################################################
cell_list = worksheet.range('E2:E10001')
i=0
 
for cell in cell_list:
  cell.value = round(rain[i],2)
  i=i+1

worksheet.update_cells(cell_list)

######################################################################
cell_list = worksheet.range('F2:F10001')
i=0
 
for cell in cell_list:
  cell.value = round(inst[i])
  i=i+1

worksheet.update_cells(cell_list)

cell_list[0]="CONSUMPTION"