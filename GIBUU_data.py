#!/usr/bin/env python
# coding: utf-8

# In[48]:


#double differential scattering cross-sections : GIBUU vs data (Normalized one)
#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

import ROOT
from ROOT import TCanvas, TGraph, gPad
from ROOT import gROOT
from array import array


get_ipython().run_line_magic('jsroot', 'on')

f = ROOT.TFile.Open("/Users/sxy1439/Documents/sbnd/workarea/clot.root","READ")
#canvas1 = ROOT.TCanvas("Canvas1","plot 1",800,600)
c1 = ROOT.TCanvas("Canvas1","plot 1")
#c1.Print("plots.pdf[")
c1.SetGrid()

tree = f.Get("bins_1_5")
scale = tree.Integral()
tree.Scale(1/scale)

#scale = 100
#tree.Scale(1/scale)


#c1.SetFillColor( 42 )
#c1.SetGrid()


#x=[1,2,3,4,5]
x=[0.25,0.75,1.25,1.75,2.25]
x_error=[1,1,1,1,1]
y=[0.038,0.25,0.22,0.041,-0.0009]
y_error=[0.038, 0.15, 0.13, 0.036, 0.0029]

gr = TGraph(len(x), array('d', x), array('d', y))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

tree.Draw('HIST')
gr.Draw( '*, same')
c1.Draw()
#c1.Update()
#c1.Print()

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c2 = ROOT.TCanvas("Canvas2","plot 2")
#c1.Print("plots.pdf[")
c2.SetGrid()

tree_2 = f.Get("bins_6_10")
scale_2 = tree_2.Integral()
tree_2.Scale(1/scale_2)


#x=[1,2,3,4,5]
x_2=[0.25,0.75,1.25,1.75,2.25]
x_error_2=[1,1,1,1,1]
y_2=[0.014,0.22,0.29,0.059,-0.0002]
y_error_2=[0.033, 0.13, 0.13, 0.034, 0.0032]

gr_2 = TGraph(len(x_2), array('d', x_2), array('d', y_2))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

tree_2.Draw('HIST')
gr_2.Draw( '*, same')
c2.Draw()

#x=[6,7,8,9,10]
#y=[0.014,0.22,0.29,0.059,-0.0002]
#y_error=[0.033, 0.13, 0.13, 0.034, 0.0032]


#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c3 = ROOT.TCanvas("Canvas3","plot 3")
#c1.Print("plots.pdf[")
c3.SetGrid()

tree_3 = f.Get("bins_11_15")
scale_3 = tree_3.Integral()
tree_3.Scale(1/scale_3)


x_3=[0.25,0.75,1.25,1.75,2.25]
x_error_3=[1,1,1,1,1]
y_3=[-0.031,0.47,0.67,0.13,-0.011]
y_error_3=[0.075, 0.27, 0.28, 0.08, 0.025]

gr_3 = TGraph(len(x_3), array('d', x_3), array('d', y_3))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_3.Draw('*')
tree_3.Draw('HIST, same')
c3.Draw()

#x=[11,12,13,14,15]
#y=[-0.031,0.47,0.67,0.13,-0.011]
#y_error=[0.075, 0.27, 0.28, 0.08, 0.025]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c4 = ROOT.TCanvas("Canvas4","plot 4")
#c1.Print("plots.pdf[")
c4.SetGrid()

tree_4 = f.Get("bins_16_19")
scale_4 = tree_4.Integral()
tree_4.Scale(1/scale_4)


x_4=[0.25,0.75,1.25,1.75,2.25]
x_error_4=[1,1,1,1,1]
y_4=[0.21,0.78,0.35,-0.013]
y_error_4=[0.13,0.32,0.11,0.024]

gr_4 = TGraph(len(x_4), array('d', x_4), array('d', y_4))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_4.Draw('*')
tree_4.Draw('HIST, same')
c4.Draw()

#x=[16,17,18,19]
#y=[0.21,0.78,0.35,-0.013]
#y_error=[0.13,0.32,0.11,0.024]


#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c5 = ROOT.TCanvas("Canvas5","plot 5")
#c1.Print("plots.pdf[")
c5.SetGrid()

tree_5 = f.Get("bins_20_23")
scale_5 = tree_5.Integral()
tree_5.Scale(1/scale_5)


x_5=[0.25,0.75,1.25,1.75,2.25]
x_error_5=[1,1,1,1,1]
y_5=[0.24,1.02,0.64,0.018]
y_error_5=[0.12,0.31,0.17,0.018]

gr_5 = TGraph(len(x_5), array('d', x_5), array('d', y_5))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_5.Draw('*')
tree_5.Draw('HIST, same')
c5.Draw()

#x=[20,21,22,23]
#y=[0.24,1.02,0.64,0.018]
#y_error=[0.12,0.31,0.17,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c6 = ROOT.TCanvas("Canvas6","plot 6")
#c1.Print("plots.pdf[")
c6.SetGrid()

tree_6 = f.Get("bins_24_27")
scale_6 = tree_6.Integral()
tree_6.Scale(1/scale_6)


x_6=[0.25,0.75,1.25,1.75,2.25]
x_error_6=[1,1,1,1,1]
y_6=[0.25,1.25,1.12,0.074]
y_error_6=[0.079,0.27,0.26,0.022]

gr_6 = TGraph(len(x_6), array('d', x_6), array('d', y_6))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_6.Draw('*')
tree_6.Draw('HIST, same')
c6.Draw()

#x=[24,25,26,27]
#y=[0.25,1.25,1.12,0.074]
#y_error=[0.079,0.27,0.26,0.022]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c7 = ROOT.TCanvas("Canvas7","plot 7")
#c1.Print("plots.pdf[")
c7.SetGrid()

tree_7 = f.Get("bins_28_32")
scale_7 = tree_7.Integral()
tree_7.Scale(1/scale_7)


x_7=[0.25,0.75,1.25,1.75,2.25]
x_error_7=[1,1,1,1,1]
y_7=[0.181,0.93,1.53,0.69,0.034]
y_error_7=[0.075,0.26,0.28,0.15,0.018]

gr_7 = TGraph(len(x_7), array('d', x_7), array('d', y_7))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_7.Draw('*')
tree_7.Draw('HIST, same')
c7.Draw()

#x=[28,29,30,31,32]
#y=[0.181,0.93,1.53,0.69,0.034]
#y_error=[0.075,0.26,0.28,0.15,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c8 = ROOT.TCanvas("Canvas8","plot 8")
#c1.Print("plots.pdf[")
c8.SetGrid()

tree_8 = f.Get("bins_33_37")
scale_8 = tree_8.Integral()
tree_8.Scale(1/scale_8)


x_8=[0.25,0.75,1.25,1.75,2.25]
x_error_8=[1,1,1,1,1]
y_8=[0.23,0.96,1.80,1.18,0.097]
y_error_8=[0.11,0.25,0.29,0.18,0.018]

gr_8 = TGraph(len(x_8), array('d', x_8), array('d', y_8))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_8.Draw('*')
tree_8.Draw('HIST, same')
c8.Draw()

#x=[33,34,35,36,37]
#y=[0.23,0.96,1.80,1.18,0.097]
#y_error=[0.11,0.25,0.29,0.18,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c9 = ROOT.TCanvas("Canvas9","plot 9")
#c1.Print("plots.pdf[")
c9.SetGrid()

tree_9 = f.Get("bins_38_42")
scale_9 = tree_9.Integral()
tree_9.Scale(1/scale_9)


x_9=[0.25,0.75,1.25,1.75,2.25]
x_error_9=[1,1,1,1,1]
y_9=[0.18,0.98,1.69,1.39,0.194]
y_error_9=[0.13,0.32,0.33,0.27,0.045]

gr_9 = TGraph(len(x_9), array('d', x_9), array('d', y_9))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
#gr.SetTitle( 'a simple graph' )

gr_9.Draw('*')
tree_9.Draw('HIST, same')
c9.Draw()

#x=[38,39,40,41,42]
#y=[0.18,0.98,1.69,1.39,0.194]
#y_error=[0.13,0.32,0.33,0.27,0.045]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


# In[55]:


#double differential scattering cross-sections : GIBUU vs data  (Scaling by 100)
#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

import ROOT
from ROOT import TCanvas, TGraph, gPad
from ROOT import gROOT
from array import array


get_ipython().run_line_magic('jsroot', 'on')

f = ROOT.TFile.Open("/Users/sxy1439/Documents/sbnd/workarea/clot.root","READ")
#canvas1 = ROOT.TCanvas("Canvas1","plot 1",800,600)
c1 = ROOT.TCanvas("Canvas1","plot 1")
#c1.Print("plots.pdf[")
c1.SetGrid()

tree = f.Get("bins_1_5")
#scale = tree.Integral()
#tree.Scale(1/scale)

scale = 100
tree.Scale(1/scale)

#tree.Draw('h')
#c1.Draw()


#c2 = ROOT.TCanvas( 'c1', 'A Simple Graph Example', 700, 500 )
#c1.SetFillColor( 42 )
#c1.SetGrid()


#x=[1,2,3,4,5]
x=[0.25,0.75,1.25,1.75,2.25]
x_error=[1,1,1,1,1]
y=[0.038,0.25,0.22,0.041,-0.0009]
y_error=[0.038, 0.15, 0.13, 0.036, 0.0029]

gr = TGraph(len(x), array('d', x), array('d', y))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr.SetTitle( 'double differential scattering cross-section' )

gr.Draw( '*')
tree.Draw('HIST, same')
c1.Draw()
#c1.Update()
#c1.Print()

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c2 = ROOT.TCanvas("Canvas2","plot 2")
#c1.Print("plots.pdf[")
c2.SetGrid()

tree_2 = f.Get("bins_6_10")
#scale_2 = tree_2.Integral()
#tree_2.Scale(1/scale_2)

scale_2 = 100
tree_2.Scale(1/scale_2)

#x=[1,2,3,4,5]
x_2=[0.25,0.75,1.25,1.75,2.25]
x_error_2=[1,1,1,1,1]
y_2=[0.014,0.22,0.29,0.059,-0.0002]
y_error_2=[0.033, 0.13, 0.13, 0.034, 0.0032]

gr_2 = TGraph(len(x_2), array('d', x_2), array('d', y_2))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr_2.SetTitle( 'double differential scattering cross-section' )

gr_2.Draw( '*')
tree_2.Draw('HIST, same')
c2.Draw()

#x=[6,7,8,9,10]
#y=[0.014,0.22,0.29,0.059,-0.0002]
#y_error=[0.033, 0.13, 0.13, 0.034, 0.0032]


#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c3 = ROOT.TCanvas("Canvas3","plot 3")
#c1.Print("plots.pdf[")
c3.SetGrid()

tree_3 = f.Get("bins_11_15")
#scale_3 = tree_3.Integral()
#tree_3.Scale(1/scale_3)

scale_3 = 100
tree_3.Scale(1/scale_3)

x_3=[0.25,0.75,1.25,1.75,2.25]
x_error_3=[1,1,1,1,1]
y_3=[-0.031,0.47,0.67,0.13,-0.011]
y_error_3=[0.075, 0.27, 0.28, 0.08, 0.025]

gr_3 = TGraph(len(x_3), array('d', x_3), array('d', y_3))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr.SetTitle( 'double differential scattering cross-section' )

gr_3.Draw('*')
tree_3.Draw('HIST, same')
c3.Draw()

#x=[11,12,13,14,15]
#y=[-0.031,0.47,0.67,0.13,-0.011]
#y_error=[0.075, 0.27, 0.28, 0.08, 0.025]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


c4 = ROOT.TCanvas("Canvas4","plot 4")
#c1.Print("plots.pdf[")
c4.SetGrid()

tree_4 = f.Get("bins_16_19")
#scale_4 = tree_4.Integral()
#tree_4.Scale(1/scale_4)

scale_4 = 100
tree_4.Scale(1/scale_4)

x_4=[0.25,0.75,1.25,1.75,2.25]
x_error_4=[1,1,1,1,1]
y_4=[0.21,0.78,0.35,-0.013]
y_error_4=[0.13,0.32,0.11,0.024]

gr_4 = TGraph(len(x_4), array('d', x_4), array('d', y_4))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr.SetTitle( 'double differential scattering cross-section' )

gr_4.Draw('*')
tree_4.Draw('HIST, same')
c4.Draw()

#x=[16,17,18,19]
#y=[0.21,0.78,0.35,-0.013]
#y_error=[0.13,0.32,0.11,0.024]


#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c5 = ROOT.TCanvas("Canvas5","plot 5")
#c1.Print("plots.pdf[")
c5.SetGrid()

tree_5 = f.Get("bins_20_23")
#scale_5 = tree_5.Integral()
#tree_5.Scale(1/scale_5)

scale_5 = 100
tree_5.Scale(1/scale_5)

x_5=[0.25,0.75,1.25,1.75,2.25]
x_error_5=[1,1,1,1,1]
y_5=[0.24,1.02,0.64,0.018]
y_error_5=[0.12,0.31,0.17,0.018]

gr_5 = TGraph(len(x_5), array('d', x_5), array('d', y_5))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr.SetTitle( 'double differential scattering cross-section' )

gr_5.Draw('*')
tree_5.Draw('HIST, same')
c5.Draw()

#x=[20,21,22,23]
#y=[0.24,1.02,0.64,0.018]
#y_error=[0.12,0.31,0.17,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c6 = ROOT.TCanvas("Canvas6","plot 6")
#c1.Print("plots.pdf[")
c6.SetGrid()

tree_6 = f.Get("bins_24_27")
#scale_6 = tree_6.Integral()
#tree_6.Scale(1/scale_6)

scale_6 = 100
tree_6.Scale(1/scale_6)

x_6=[0.25,0.75,1.25,1.75,2.25]
x_error_6=[1,1,1,1,1]
y_6=[0.25,1.25,1.12,0.074]
y_error_6=[0.079,0.27,0.26,0.022]

gr_6 = TGraph(len(x_6), array('d', x_6), array('d', y_6))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr.SetTitle( 'double differential scattering cross-section' )

gr_6.Draw('*')
tree_6.Draw('HIST, same')
c6.Draw()

#x=[24,25,26,27]
#y=[0.25,1.25,1.12,0.074]
#y_error=[0.079,0.27,0.26,0.022]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c7 = ROOT.TCanvas("Canvas7","plot 7")
#c1.Print("plots.pdf[")
c7.SetGrid()

tree_7 = f.Get("bins_28_32")
#scale_7 = tree_7.Integral()
#tree_7.Scale(1/scale_7)

scale_7 = 100
tree_7.Scale(1/scale_7)

x_7=[0.25,0.75,1.25,1.75,2.25]
x_error_7=[1,1,1,1,1]
y_7=[0.181,0.93,1.53,0.69,0.034]
y_error_7=[0.075,0.26,0.28,0.15,0.018]

gr_7 = TGraph(len(x_7), array('d', x_7), array('d', y_7))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr.SetTitle( 'double differential scattering cross-section' )

gr_7.Draw('*')
tree_7.Draw('HIST, same')
c7.Draw()

#x=[28,29,30,31,32]
#y=[0.181,0.93,1.53,0.69,0.034]
#y_error=[0.075,0.26,0.28,0.15,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c8 = ROOT.TCanvas("Canvas8","plot 8")
#c1.Print("plots.pdf[")
c8.SetGrid()

tree_8 = f.Get("bins_33_37")
#scale_8 = tree_8.Integral()
#tree_8.Scale(1/scale_8)

scale_8 = 100
tree_8.Scale(1/scale_8)

x_8=[0.25,0.75,1.25,1.75,2.25]
x_error_8=[1,1,1,1,1]
y_8=[0.23,0.96,1.80,1.18,0.097]
y_error_8=[0.11,0.25,0.29,0.18,0.018]

gr_8 = TGraph(len(x_8), array('d', x_8), array('d', y_8))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr.SetTitle( 'double differential scattering cross-section' )

gr_8.Draw('*')
tree_8.Draw('HIST, same')
c8.Draw()

#x=[33,34,35,36,37]
#y=[0.23,0.96,1.80,1.18,0.097]
#y_error=[0.11,0.25,0.29,0.18,0.018]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------

c9 = ROOT.TCanvas("Canvas9","plot 9")
#c1.Print("plots.pdf[")
c9.SetGrid()

tree_9 = f.Get("bins_38_42")
#scale_9 = tree_9.Integral()
#tree_9.Scale(1/scale_9)

scale_9 = 100
tree_9.Scale(1/scale_9)

x_9=[0.25,0.75,1.25,1.75,2.25]
x_error_9=[1,1,1,1,1]
y_9=[0.18,0.98,1.69,1.39,0.194]
y_error_9=[0.13,0.32,0.33,0.27,0.045]

gr_9 = TGraph(len(x_9), array('d', x_9), array('d', y_9))

#gr = ROOT.TGraphErrors(len(x), x, y, x_error, y_error)

#gr = ROOT.TGraph( x, y )
gr_9.SetTitle( 'double differential scattering cross-section' )

gr_9.Draw('*')
tree_9.Draw('HIST, same')
c9.Draw()

#x=[38,39,40,41,42]
#y=[0.18,0.98,1.69,1.39,0.194]
#y_error=[0.13,0.32,0.33,0.27,0.045]

#--------------------------------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------------------------------


# In[ ]:





# In[ ]:




