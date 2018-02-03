# Credit Card Checker
This is a simple QT project to validate a credit card number. This project contains several concepts used in QT/C++. It is probably also a little over-engineered, but the idea is to demonstrate the basic concepts.
It corrently works for credit card numbers which are 16 digits long.

## Architecture
The software is based on the model-view-controller principles:  
model: CreditCard  
view: MainWidget  
controller: EventHandler  

## Build the project
qmake -project QT+=widgets  
qmake  
make  

## Create documentation
doxygen -g  
doxygen  
