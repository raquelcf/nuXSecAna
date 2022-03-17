#!/usr/bin/env python
# coding: utf-8

# In[1]:


#with scaling by 100 and \del p_\mu and \del cosine_\mu for bins 1 to 5


import ROOT
from ROOT import TCanvas, TGraph, gPad
from ROOT import gROOT
from array import array
import scipy.stats as stats
import numpy as np

get_ipython().run_line_magic('jsroot', 'on')

f = ROOT.TFile.Open("/Users/sxy1439/Documents/sbnd/workarea/clot.root","READ")
#canvas1 = ROOT.TCanvas("Canvas1","plot 1",800,600)
c1 = ROOT.TCanvas("Canvas1","plot 1")
#c1.Print("plots.pdf[")
c1.SetGrid()

tree = f.Get("bins_1_5")
scale = 100*0.5   #0.5 is \delta cos(\theta_\mu) where -1<=cos(\theta_\mu)<-0.5
tree.Scale(1/scale)


value_bin1st = tree.GetBinContent(1)
tree.SetBinContent(1, value_bin1st/0.18)


value_bin2st = tree.GetBinContent(2)
tree.SetBinContent(2, value_bin2st/0.12)


value_bin3st = tree.GetBinContent(3)
tree.SetBinContent(3, value_bin3st/0.15)


value_bin4st = tree.GetBinContent(4)
tree.SetBinContent(4, value_bin4st/0.32)


value_bin5st = tree.GetBinContent(5)
tree.SetBinContent(5, value_bin5st/1.73)




#x=[1,2,3,4,5]
x_1=[0.25,0.75,1.25,1.75,2.25]
x_error_1=[0.25,0.25,0.25,0.25,0.25]

y_1=[0.038, 0.25, 0.22, 0.041, -0.0009]

#y_1.Scale(np.array([0.18,0.12,0.15,0.32,1.73]))
y_error_1=[0.038, 0.15, 0.13, 0.036, 0.0029]



#gr = TGraph(len(x_1), array('d', x_1), array('d', y_1))
gr =  ROOT.TGraphErrors(len(x_1), array('d', x_1), array('d', y_1), array('d',x_error_1), array('d',y_error_1))

#gr.SetTitle( 'a simple graph' )

gr.Draw('*')
tree.Draw('HIST, same')
c1.Draw()
gr.SetTitle( 'bins 1-5' )
gr.GetXaxis().SetTitle("bins");
#gr.GetYaxis().SetTitle("d^2\sigma/{dp_\mu d cos(\ theta_\mu)}($10^{-38} {cm}^2/GeV$)&#39;)");
#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c2 = ROOT.TCanvas("Canvas2","plot 2")
#c1.Print("plots.pdf[")
c2.SetGrid()

tree_2 = f.Get("bins_6_10")
scale_2 = 100*0.5    #0.5 is \delta cos(\theta_\mu) where -0.5<=cos(\theta_\mu)<0
tree_2.Scale(1/scale_2)

value_bin1_2st = tree_2.GetBinContent(1)
tree_2.SetBinContent(1, value_bin1_2st/0.18)


value_bin2_2st = tree_2.GetBinContent(2)
tree_2.SetBinContent(2, value_bin2_2st/0.12)


value_bin3_2st = tree_2.GetBinContent(3)
tree_2.SetBinContent(3, value_bin3_2st/0.15)


value_bin4_2st = tree_2.GetBinContent(4)
tree_2.SetBinContent(4, value_bin4_2st/0.32)


value_bin5_2st = tree_2.GetBinContent(5)
tree_2.SetBinContent(5, value_bin5_2st/1.73)





#x=[1,2,3,4,5]
x_2=[0.25,0.75,1.25,1.75,2.25]
x_error_2=[0.25,0.25,0.25,0.25,0.25]
y_2=[0.014,0.22,0.29,0.059,-0.0002]
y_error_2=[0.033, 0.13, 0.13, 0.034, 0.0032]

gr_2 =  ROOT.TGraphErrors(len(x_2), array('d', x_2), array('d', y_2), array('d',x_error_2), array('d',y_error_2))


#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_2.Draw( '*')
tree_2.Draw('HIST, same')

c2.Draw()
gr_2.SetTitle( 'bins 6-10' )

#x=[6,7,8,9,10]
#y=[0.014,0.22,0.29,0.059,-0.0002]
#y_error=[0.033, 0.13, 0.13, 0.034, 0.0032]


#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c3 = ROOT.TCanvas("Canvas3","plot 3")
#c1.Print("plots.pdf[")
c3.SetGrid()

tree_3 = f.Get("bins_11_15")
scale_3 = 100*0.27    #0.27 is \delta cos(\theta_\mu) where 0<=cos(\theta_\mu)<0.27
tree_3.Scale(1/scale_3)



value_bin1_3st = tree_3.GetBinContent(1)
tree_3.SetBinContent(1, value_bin1_3st/0.18)


value_bin2_3st = tree_3.GetBinContent(2)
tree_3.SetBinContent(2, value_bin2_3st/0.12)


value_bin3_3st = tree_3.GetBinContent(3)
tree_3.SetBinContent(3, value_bin3_3st/0.15)


value_bin4_3st = tree_3.GetBinContent(4)
tree_3.SetBinContent(4, value_bin4_3st/0.32)


value_bin5_3st = tree_3.GetBinContent(5)
tree_3.SetBinContent(5, value_bin5_3st/1.73)




x_3=[0.25,0.75,1.25,1.75,2.25]
x_error_3=[0.25,0.25,0.25,0.25,0.25]
y_3=[-0.031,0.47,0.67,0.13,-0.011]
y_error_3=[0.075, 0.27, 0.28, 0.08, 0.025]

gr_3 =  ROOT.TGraphErrors(len(x_3), array('d', x_3), array('d', y_3), array('d',x_error_3), array('d',y_error_3))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_3.Draw('*')
tree_3.Draw('HIST, same')
c3.Draw()
gr_3.SetTitle( 'bins 11-15' )
#x=[11,12,13,14,15]
#y=[-0.031,0.47,0.67,0.13,-0.011]
#y_error=[0.075, 0.27, 0.28, 0.08, 0.025]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c4 = ROOT.TCanvas("Canvas4","plot 4")
#c1.Print("plots.pdf[")
c4.SetGrid()

tree_4 = f.Get("bins_16_19")
scale_4 = 100*0.18         #0.18 is \delta cos(\theta_\mu) where 0.27<=cos(\theta_\mu)<0.45
tree_4.Scale(1/scale_4)


value_bin1_4st = tree_4.GetBinContent(1)
tree_4.SetBinContent(1, value_bin1_4st/0.18)


value_bin2_4st = tree_4.GetBinContent(2)
tree_4.SetBinContent(2, value_bin2_4st/0.12)


value_bin3_4st = tree_4.GetBinContent(3)
tree_4.SetBinContent(3, value_bin3_4st/0.15)


value_bin4_4st = tree_4.GetBinContent(4)
tree_4.SetBinContent(4, value_bin4_4st/0.32)


value_bin5_4st = tree_4.GetBinContent(5)
tree_4.SetBinContent(5, value_bin5_4st/1.73)




x_4=[0.3125,0.9375,1.5625,2.1875]
x_error_4=[0.25,0.25,0.25,0.25]
y_4=[0.21,0.78,0.35,-0.013]
y_error_4=[0.13,0.32,0.11,0.024]

gr_4 =  ROOT.TGraphErrors(len(x_4), array('d', x_4), array('d', y_4), array('d',x_error_4), array('d',y_error_4))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_4.Draw('*')
tree_4.Draw('HIST, same')
c4.Draw()
gr_4.SetTitle( 'bins 16-19' )
#x=[16,17,18,19]
#y=[0.21,0.78,0.35,-0.013]
#y_error=[0.13,0.32,0.11,0.024]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c5 = ROOT.TCanvas("Canvas5","plot 5")
#c1.Print("plots.pdf[")
c5.SetGrid()

tree_5 = f.Get("bins_20_23")
scale_5 = 100*0.17    #0.17 is \delta cos(\theta_\mu) where 0.45<=cos(\theta_\mu)<0.62
tree_5.Scale(1/scale_5)


value_bin1_5st = tree_5.GetBinContent(1)
tree_5.SetBinContent(1, value_bin1_5st/0.30)


value_bin2_5st = tree_5.GetBinContent(2)
tree_5.SetBinContent(2, value_bin2_5st/0.15)


value_bin3_5st = tree_5.GetBinContent(3)
tree_5.SetBinContent(3, value_bin3_5st/0.32)


value_bin4_5st = tree_5.GetBinContent(4)
tree_5.SetBinContent(4, value_bin4_5st/0.73)




x_5=[0.3125,0.9375,1.5625,2.1875]
x_error_5=[0.25,0.25,0.25,0.25,0.25]
y_5=[0.24,1.02,0.64,0.018]
y_error_5=[0.12,0.31,0.17,0.018]

gr_5 =  ROOT.TGraphErrors(len(x_5), array('d', x_5), array('d', y_5), array('d',x_error_5), array('d',y_error_5))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_5.Draw('*')
tree_5.Draw('HIST, same')
c5.Draw()
gr_5.SetTitle( 'bins 20-23' )
#x=[20,21,22,23]
#y=[0.24,1.02,0.64,0.018]
#y_error=[0.12,0.31,0.17,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c6 = ROOT.TCanvas("Canvas6","plot 6")
#c1.Print("plots.pdf[")
c6.SetGrid()

tree_6 = f.Get("bins_24_27")
scale_6 = 100*0.14     #0.14 is \delta cos(\theta_\mu) where 0.62<=cos(\theta_\mu)<0.76
tree_6.Scale(1/scale_6)


value_bin1_6st = tree_6.GetBinContent(1)
tree_6.SetBinContent(1, value_bin1_6st/0.30)


value_bin2_6st = tree_6.GetBinContent(2)
tree_6.SetBinContent(2, value_bin2_6st/0.15)


value_bin3_6st = tree_6.GetBinContent(3)
tree_6.SetBinContent(3, value_bin3_6st/0.32)


value_bin4_6st = tree_6.GetBinContent(4)
tree_6.SetBinContent(4, value_bin4_6st/1.73)



x_6=[0.3125,0.9375,1.5625,2.1875]
x_error_6=[0.25,0.25,0.25,0.25]
y_6=[0.25,1.25,1.12,0.074]
y_error_6=[0.079,0.27,0.26,0.022]

gr_6 =  ROOT.TGraphErrors(len(x_6), array('d', x_6), array('d', y_6), array('d',x_error_6), array('d',y_error_6))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_6.Draw('*')
tree_6.Draw('HIST, same')
c6.Draw()
gr_6.SetTitle( 'bins 24-27' )
#x=[24,25,26,27]
#y=[0.25,1.25,1.12,0.074]
#y_error=[0.079,0.27,0.26,0.022]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c7 = ROOT.TCanvas("Canvas7","plot 7")
#c1.Print("plots.pdf[")
c7.SetGrid()

tree_7 = f.Get("bins_28_32")
scale_7 = 100*0.10       #0.10 is \delta cos(\theta_\mu) where 0.76<=cos(\theta_\mu)<0.86
tree_7.Scale(1/scale_7)


value_bin1_7st = tree_7.GetBinContent(1)
tree_7.SetBinContent(1, value_bin1_7st/0.30)


value_bin2_7st = tree_7.GetBinContent(2)
tree_7.SetBinContent(2, value_bin2_7st/0.15)


value_bin3_7st = tree_7.GetBinContent(3)
tree_7.SetBinContent(3, value_bin3_7st/0.32)


value_bin4_7st = tree_7.GetBinContent(4)
tree_7.SetBinContent(4, value_bin4_7st/1.73)


x_7=[0.25,0.75,1.25,1.75,2.25]
x_error_7=[0.25,0.25,0.25,0.25,0.25]
y_7=[0.181,0.93,1.53,0.69,0.034]
y_error_7=[0.075,0.26,0.28,0.15,0.018]

gr_7 =  ROOT.TGraphErrors(len(x_7), array('d', x_7), array('d', y_7), array('d',x_error_7), array('d',y_error_7))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

tree_7.Draw('HIST')
gr_7.Draw('*, same')
c7.Draw()
gr_7.SetTitle( 'bins 28-32' )
#x=[28,29,30,31,32]
#y=[0.181,0.93,1.53,0.69,0.034]
#y_error=[0.075,0.26,0.28,0.15,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c8 = ROOT.TCanvas("Canvas8","plot 8")
#c1.Print("plots.pdf[")
c8.SetGrid()

tree_8 = f.Get("bins_33_37")
scale_8 = 100*0.08       #0.08 is \delta cos(\theta_\mu) where 0.86<=cos(\theta_\mu)<0.94
tree_8.Scale(1/scale_8)

value_bin1_8st = tree_8.GetBinContent(1)
tree_8.SetBinContent(1, value_bin1_8st/0.30)


value_bin2_8st = tree_8.GetBinContent(2)
tree_8.SetBinContent(2, value_bin2_8st/0.15)


value_bin3_8st = tree_8.GetBinContent(3)
tree_8.SetBinContent(3, value_bin3_8st/0.32)


value_bin4_8st = tree_8.GetBinContent(4)
tree_8.SetBinContent(4, value_bin4_8st/0.51)


value_bin5_8st = tree_8.GetBinContent(5)
tree_8.SetBinContent(5, value_bin5_8st/1.22)


x_8=[0.25,0.75,1.25,1.75,2.25]
x_error_8=[0.25,0.25,0.25,0.25,0.25]
y_8=[0.23,0.96,1.80,1.18,0.097]
y_error_8=[0.11,0.25,0.29,0.18,0.018]

gr_8 =  ROOT.TGraphErrors(len(x_8), array('d', x_8), array('d', y_8), array('d',x_error_8), array('d',y_error_8))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_8.Draw('*')
tree_8.Draw('HIST, same')
c8.Draw()
gr_8.SetTitle( 'bins 33-37' )
#x=[33,34,35,36,37]
#y=[0.23,0.96,1.80,1.18,0.097]
#y_error=[0.11,0.25,0.29,0.18,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c9 = ROOT.TCanvas("Canvas9","plot 9")
#c1.Print("plots.pdf[")
c9.SetGrid()

tree_9 = f.Get("bins_38_42")
scale_9 = 100*0.06     #0.06 is \delta cos(\theta_\mu) where 0.94<=cos(\theta_\mu)<1
tree_9.Scale(1/scale_9)

value_bin1_9st = tree_9.GetBinContent(1)
tree_9.SetBinContent(1, value_bin1_9st/0.30)


value_bin2_9st = tree_9.GetBinContent(2)
tree_9.SetBinContent(2, value_bin2_9st/0.15)


value_bin3_9st = tree_9.GetBinContent(3)
tree_9.SetBinContent(3, value_bin3_9st/0.32)


value_bin4_9st = tree_9.GetBinContent(4)
tree_9.SetBinContent(4, value_bin4_9st/0.51)


value_bin5_9st = tree_9.GetBinContent(5)
tree_9.SetBinContent(5, value_bin5_9st/1.22)



x_9=[0.25,0.75,1.25,1.75,2.25]
x_error_9=[0.25,0.25,0.25,0.25,0.25]
y_9=[0.18,0.98,1.69,1.39,0.194]
y_error_9=[0.13,0.32,0.33,0.27,0.045]

gr_9 =  ROOT.TGraphErrors(len(x_9), array('d', x_9), array('d', y_9), array('d',x_error_9), array('d',y_error_9))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr_9.SetTitle( 'double differential scattering cross-section' )

gr_9.Draw('*')
tree_9.Draw('HIST, same')
c9.Draw()
gr_9.SetTitle( 'bins 38-42' )
#x=[38,39,40,41,42]
#y=[0.18,0.98,1.69,1.39,0.194]
#y_error=[0.13,0.32,0.33,0.27,0.045]


#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

## Chi Square test



observed = np.array([0.038,0.25,0.22,0.041,-0.0009,0.014,0.22,0.29,0.059,-0.0002,-0.031,0.47,0.67,0.13,-0.011,0.21,0.78,0.35,-0.013,0.24,1.02,0.64,0.018,0.25,1.25,1.12,0.074,0.181,0.93,1.53,0.69,0.034,0.23,0.96,1.80,1.18,0.097,0.18,0.98,1.69,1.39,0.194])
expected = np.array([0.02914,0.2440,0.1305,0.01696,0.000681,0.04000,0.3709,0.2950,0.04686,0.002105,0.05430,0.6383,0.7207,0.1959,0.007830,0.5425,1.179,0.8581,0.07592,0.3239,1.114,0.7186,0.08969,0.3230,1.228,1.214,0.1090,0.2893,1.225,1.640,0.2284,0.06723,0.2808,1.228,1.911,1.523,0.1899,0.3329,1.230,1.863,1.863,0.3295])
#print(observed)
#print(expected)

chi_square_stat = (((observed - expected)**2)/expected).sum()

print(chi_square_stat)

crit = stats.chi2.ppf(q = 0.95, #determining the critical value at 95% confidence level
                      df = 4 ) #df = degrees of freedom
print("Critical value")
print(crit)
    
p_value = 1 - stats.chi2.cdf(x = chi_square_stat, df = 4)
    
print("P Value")
print(p_value)

if abs(chi_square_stat)>=crit:
    print("Dependent, rejects null hypothesis")

else:
    print("Independent, fails to rejects null hypothesis")



# In[61]:


import ROOT
from ROOT import TCanvas, TGraph, gPad
from ROOT import gROOT
from array import array
import scipy.stats as stats
import numpy as np

get_ipython().run_line_magic('jsroot', 'on')

f = ROOT.TFile.Open("/Users/sxy1439/Documents/sbnd/workarea/clot.root","READ")
#canvas1 = ROOT.TCanvas("Canvas1","plot 1",800,600)
c7 = ROOT.TCanvas("Canvas7","plot 7")
#c1.Print("plots.pdf[")
c7.SetGrid()

tree_7 = f.Get("bins_28_32")
scale_7 = 100*0.10       #0.10 is \delta cos(\theta_\mu) where 0.76<=cos(\theta_\mu)<0.86
tree_7.Scale(1/scale_7)


value_bin1_7st = tree_7.GetBinContent(1)
tree_7.SetBinContent(1, value_bin1_7st/0.30)


value_bin2_7st = tree_7.GetBinContent(2)
tree_7.SetBinContent(2, value_bin2_7st/0.15)


value_bin3_7st = tree_7.GetBinContent(3)
tree_7.SetBinContent(3, value_bin3_7st/0.32)


value_bin4_7st = tree_7.GetBinContent(4)
tree_7.SetBinContent(4, value_bin4_7st/1.73)


x_7=[0.25,0.75,1.25,1.75,2.25]
x_error_7=[0.25,0.25,0.25,0.25,0.25]
y_7=[0.181,0.93,1.53,0.69,0.034]
y_error_7=[0.075,0.26,0.28,0.15,0.018]

gr_7 =  ROOT.TGraphErrors(len(x_7), array('d', x_7), array('d', y_7), array('d',x_error_7), array('d',y_error_7))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

tree_7.Draw('HIST')
gr_7.Draw('*, same')
c7.Draw()
gr_7.SetTitle( 'bins 28-32' )
#x=[28,29,30,31,32]
#y=[0.181,0.93,1.53,0.69,0.034]
#y_error=[0.075,0.26,0.28,0.15,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


# In[ ]:




