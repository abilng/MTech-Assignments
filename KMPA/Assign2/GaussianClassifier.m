
function GaussianClassifier(DataRoot,NaiveBayes)
%{

CLASSIFIER : Function to train a system to classify a given element to any
of the classes using BAYES and NAIVE-BAYES Classifier; and to find the
Classification Accuracy, Confusion Matrix and Decision Region Plot of the
classifier.

Input
qns - Path to a folder containing the data(3 seperate classes).

Description
This code will work only for a 3 class problem. Each class has to be
specified separately in text files and path is given as input to the
function.

%}

%{
class1_test.txt   class2_test.txt   class3_test.txt
class1_train.txt  class2_train.txt  class3_train.txt
class1_val.txt    class2_val.txt    class3_val.txt
%}

%Loading the Data


class1Train = load(strcat(DataRoot,'/class1_train.txt'));
class2Train = load(strcat(DataRoot,'/class2_train.txt'));
class3Train = load(strcat(DataRoot,'/class3_train.txt'));

class1Test = load(strcat(DataRoot,'/class1_test.txt'));
class2Test = load(strcat(DataRoot,'/class2_test.txt'));
class3Test = load(strcat(DataRoot,'/class3_test.txt'));

class1Val = load(strcat(DataRoot,'/class1_val.txt'));
class2Val = load(strcat(DataRoot,'/class2_val.txt'));
class3Val = load(strcat(DataRoot,'/class3_val.txt'));



%estimateing the Class
[ class1Mean, class1Var] = estimate(class1Train);
[ class2Mean, class2Var] = estimate(class2Train);
[ class3Mean, class3Var] = estimate(class3Train);


if NaiveBayes
    class1Var = diag(diag(class1Var));
    class2Var = diag(diag(class2Var));
    class3Var = diag(diag(class3Var));
end

%Confusion Matrix
ConfMat(1:3,1:3) = 0;
%Classification Accuracy
Accu(1:3) = 0;
    
%Finding the Decision Regions
for x = 1:3
    
    if x== 1
            test = class1Test;
    elseif x == 2
            test = class2Test;
    else
            test = class3Test;
    end
    for p = 1:size(test,1)
        X = test(p,:);
        class = getClass(X, class1Mean, class1Var, class2Mean, class2Var, class3Mean, class3Var);
        ConfMat(x,class) = ConfMat(x,class) + 1;    
    end
    Accu(x) = ConfMat(x,x) / sum(ConfMat(x,:));
end
disp('Confusion Matrix');
disp(ConfMat);
disp('Classification Accuracy');
disp(Accu);
disp('Average Accuracy');
disp(mean(Accu));



gA= @(x,y) discriFun([x,y], class1Mean, class1Var);
gB= @(x,y) discriFun([x y], class2Mean, class2Var);
gC= @(x,y) discriFun([x y], class3Mean, class3Var);

plotClassifer(class1Train,class2Train,class3Train,gA,gB,gC);
if NaiveBayes
    title('Decision Boundaries - Bayes classifier (Gaussian model -NaiveBayes) ');
else
    title('Decision Boundaries - Bayes classifier (Gaussian model)');
end
hold off;
end


function [classMean, classVar] = estimate(train)
%estimate : find the Mean and Covariance matrices of that Training data.
classMean = mean(train);
classVar = cov(train);
end

function class = getClass( X, mA, cA, mB, cB, mC, cC)

%{

GETCLASS : Function to find, X belongs to which Class.

Input
X - Element to be classified.
mA - Mean of class A.
cA - Covariance of class A.
mB - Mean of class B.
cB - Covariance of class B.
mC - Mean of class C.
cC - Covariance of class C.

Output
class - Class of the element X.

Decription


%}

gA= discriFun( X, mA, cA);
gB= discriFun( X, mB, cB);
gC= discriFun( X, mC, cC);

[~,class] = max([gA,gB,gC]);

end

function g = discriFun( X, M, C)

%DISCRI_FUN : Function to find the value of Discriminant Function.

g = -((X-M)/C*(X-M)'+log(abs(det(C))))/2+ (1/3);

end

function plotClassifer(classA,classB,classC,gA,gB,gC)
%{

PLOTCLASSIFIER - Function to plot the data and decision boundaries.
ClassA,ClassB,ClassC - Tarin data
gA,gB,gC - handle to decision surface
%}
    figure;
    syms x y;
    class = [classA;classB;classC];
    xmin = min(class(:,1)) - 5;
    xmax = max(class(:,1)) + 5;
    ymin = min(class(:,2)) - 5;
    ymax = max(class(:,2)) + 5;
    scatter(classA(:,1),classA(:,2),'*');hold on;
    scatter(classB(:,1),classB(:,2),'r*');hold on;
    scatter(classC(:,1),classC(:,2),'g*');hold on;
    s = warning('off','all');
    gplot = ezsurf(gA,[xmin,xmax,ymin,ymax]);hold on;
    set(gplot, 'FaceColor', [0 128 128] / 256);
    gplot = ezsurf(gB,[xmin,xmax,ymin,ymax]);hold on;
    set(gplot, 'FaceColor', [128 128 0] / 256);
    gplot = ezsurf(gC,[xmin,xmax,ymin,ymax]);hold on;
    set(gplot, 'FaceColor', [0 0 128] / 256);
    warning(s);
    xlabel('x');
    ylabel('y');

end
