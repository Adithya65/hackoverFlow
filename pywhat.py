#!/usr/bin/env python
# coding: utf-8

# In[1]:


get_ipython().system('pip install google_spreadsheet')
get_ipython().system('pip install google-auth-oauthlib')
get_ipython().system('pip install pandas')
get_ipython().system('pip install gspread')


# In[2]:


import gspread
import pywhatkit as kit
 

from oauth2client.service_account import ServiceAccountCredentials

from pprint import pprint

scope = ["https://spreadsheets.google.com/feeds",'https://www.googleapis.com/auth/spreadsheets',"https://www.googleapis.com/auth/drive.file","https://www.googleapis.com/auth/drive"]

creds = ServiceAccountCredentials.from_json_keyfile_name("creds.json",scope)
client = gspread.authorize(creds)

sheet = client.open("Pendullum_final").sheet1



 
 


# In[ ]:



col = sheet.col_values(8)
for i in range(100 ):
   if col[i]=="error":
       kit.sendwhatmsg("+919*********", "Error in the Meter!", 18, 21)
       break
   

