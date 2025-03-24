# -*- coding: utf-8 -*-
"""
Created on Mon Feb 10 18:13:23 2025

@author: Sean Kovar

Note: Make sure the there is a folder named "data" in the same folder as this python file. 

Variable names: https://www.ndbc.noaa.gov/faq/measdes.shtml
    Use this link to learn about the types of data
    
"""
import numpy as np
import os
import urllib.request
import pandas as pd
import matplotlib.pyplot as plt
from datetime import date


# get data first
currentDate = str(date.today())
url = 'https://www.ndbc.noaa.gov/data/5day2/42035_5day.txt'
fname='data/42035_5day_'+currentDate+'.txt'
if not os.path.exists(fname):
    print('Downloading',fname)
    urllib.request.urlretrieve(url,fname)


file = pd.read_csv(fname, sep='\s+')

    
#function takes in the name of a measurement in the meterological data file and saves a graph of the data over the last 5 days
def graph_Variable(dataname):
    var = np.array(file[dataname])
    i = 0
    days = []; minutes = []; hours = [];varx = []
    for ix in var:
        # Some of the data points are not present in the data. 
        try:
            var[i] = float(var[i])
            
            varx.append(float(var[i]))
            days.append(int(file['DD'][i]))
            minutes.append(int(file['mm'][i]))
            hours.append(int(file['hh'][i]))
        except:
            print("no float at "+ str(i))
        i += 1
        
    #creating the time variable list 
    time = np.zeros(len(varx))
    time = np.array(days)*10000+np.array(minutes)+np.array(hours)*100
    
    #creating the figure
    plt.figure(figsize=[8,4])
    plt.plot(time, varx)
    plt.title("5 day "+dataname+" starting at "+str(time[-1]))
    plt.xlabel("Time in DDhhmm")
    plt.ylabel(dataname +" in "+str(file[dataname][0]))
    
    #saving the figure
    figname=f'graph_of_{dataname+currentDate}'
    print(figname); plt.savefig(figname,dpi=100)
    return(time,varx)



graph_Variable('GST') #Gust wind speed

graph_Variable('WVHT') #Mean Wave Height

graph_Variable('WDIR') #Wind direction

graph_Variable('MWD') #Mean Wave Direction

graph_Variable('PTDY') #Pressure Tendency
