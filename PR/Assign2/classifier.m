%Pattern Recognition : Assignment 2

function classifier(qns)

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

%Loading the Data
class1 = load(strcat(qns,'/class1.txt'));
class2 = load(strcat(qns,'/class2.txt'));
class3 = load(strcat(qns,'/class3.txt'));


%Partitioning the Class
[class1Test, class1Mean, class1Var, class1Size, class1TestSize] = partition(class1);
[class2Test, class2Mean, class2Var, class2Size, class2TestSize] = partition(class2);
[class3Test, class3Mean, class3Var, class3Size, class3TestSize] = partition(class3);

%Variance of the whole data
class = [class1;class2;class3];
classVar = cov(class);
sig = mean2(diag(cov(class)));

%Calculating Probability of each class
n = class1Size + class2Size + class3Size;
pr1 = log(class1Size/n);
pr2 = log(class2Size/n);
pr3 = log(class3Size/n);

for probNo = 1:5
    
    if probNo == 1
        disp('1. Bayes classifier - Covariance matrix for each class is different');
    elseif probNo == 2
        disp('2. Bayes classifier - Covariance matrix for all the classes is the same and is C');
    elseif probNo == 3
        disp('3. Naive-Bayes classifier - Covariance matrix for each class is different');
    elseif probNo == 4
        disp('4. Naive-Bayes classifier - Covariance matrix for all the classes is the same and is the C');
    else
        disp('5. Naive-Bayes classifier - Covariance matrix for all the classes is the same and is sigma2I');
    end
    
    %Confusion Matrix
    ConfMat(1:3,1:3) = 0;
    %Classification Accuracy
    Accu(1:3) = 0;
    
    %Ploting the Data
    plotClassifer(class1,class2,class3,class1Mean, class1Var, class2Mean, class2Var, class3Mean, class3Var, pr1, pr2, pr3, classVar, sig,probNo);
    
    %Finding the Decision Regions
    for s = 1:3
        
        if s== 1
            q= class1TestSize;
            test = class1Test;
        elseif s == 2
            q= class2TestSize;
            test = class2Test;
        else
            q= class3TestSize;
            test = class3Test;
        end
        
        
        for p = 1:q
            X = test(p,:);
            class = getClass(probNo, X, class1Mean, class1Var, class2Mean, class2Var, class3Mean, class3Var, pr1, pr2, pr3, classVar, sig);
            if class == 'A'
                ConfMat(s,1) = ConfMat(s,1) + 1;
            elseif class == 'B'
                ConfMat(s,2) = ConfMat(s,2) + 1;
            else
                ConfMat(s,3) = ConfMat(s,3) + 1;
            end
        end
        Accu(s) = ConfMat(s,s) / sum(ConfMat(s,:));
    end
    
    disp('Confusion Matrix');
    disp(ConfMat);
    disp('Classification Accuracy');
    disp(Accu);
    
end

end


function [test, classMean, classVar, classSize, testSize] = partition(class)

%{

PARTITION : Divides the class dataset into Training datset and Test dataset
and find the Mean and Covariance matrices of that Training data.

Input
class - Data of each class.

Output
test - Outputs the test dataset.
class_mean - Mean of the training dataset.
class_var - Variance of the training dataset.
class_size - Size of the inputed class dataset.
test_size - Size of the test dataset.

Description
Function randomly select 75% of data from class as Training data and the
remaining is taken as Test data.

%}

[classSize,~] = size(class);
index = randperm(classSize);
class = class(index,:);
trainSize = ceil(classSize*0.75);
testSize = floor(classSize*0.25);
train = class(1:trainSize,:);
test = class(trainSize+1:classSize,:);
classMean = mean(train);
classVar = cov(train);

end

function class = getClass(probNo, X, mA, cA, mB, cB, mC, cC, pr1, pr2, pr3, cClass, sig)

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

gA= discriFun(probNo, X, mA, cA, pr1, cClass, sig);
gB= discriFun(probNo, X, mB, cB, pr2, cClass, sig);
gC= discriFun(probNo, X, mC, cC, pr3, cClass, sig);

if gA > gB
    class = 'A';
    max = gA;
else
    class = 'B';
    max = gB;
end
if max < gC
    class = 'C';
end

end

function g = discriFun(probNo, X, M, C, P, cClass, sig)

%{

DISCRI_FUN : Function to find the value of Discriminant Function.

Input
x - Element to be classified.
M - Mean of the Class for which Discriminant Function is calculated.
C - Covariance of the Class for which Discriminant Function us calculated.

Output
g - Value of Discriminant Function.

Description
ProbNo
1. Bayes classifier - Covariance matrix for each class is different
2. Bayes classifier - Covariance matrix for all the classes is the same and is C
3. Naive-Bayes classifier - Covariance matrix for each class is different
4. Naive-Bayes classifier - Covariance matrix for all the classes is the same and is the C
5. Naive-Bayes classifier - Covariance matrix for all the classes is the same and is sigma2I

%}

if probNo == 1
    g = (X-M)/C*(X-M)'+log(abs(det(C)));
elseif probNo == 2
    C = cClass;
    g = (X-M)/C*(X-M)';
elseif probNo == 3
    C = diag(diag(C));
    g = (X-M)/C*(X-M)'+log(abs(det(C)));
elseif probNo == 4
    C = diag(diag(cClass));
    g = (X-M)/C*(X-M)';
else
    g = ((X-M)*(X-M)')^2 / sig;
end

g = -g/2 + P;

end

function plotClassifer(classA,classB,classC,mA, cA, mB, cB, mC, cC, pA, pB, pC, cClass, sig,type)
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
    gA= @(x,y) discriFun(type, [x,y], mA, cA, pA, cClass, sig);
    gB= @(x,y) discriFun(type, [x y], mB, cB, pB, cClass, sig);
    gC= @(x,y) discriFun(type, [x y], mC, cC, pC, cClass, sig);
    gplot = ezsurf(gA,[xmin,xmax,ymin,ymax]);hold on;
    set(gplot, 'FaceColor', [0 128 128] / 256);
    gplot = ezsurf(gB,[xmin,xmax,ymin,ymax]);hold on;
    set(gplot, 'FaceColor', [128 128 0] / 256);
    gplot = ezsurf(gC,[xmin,xmax,ymin,ymax]);hold on;
    set(gplot, 'FaceColor', [0 0 128] / 256);
    warning(s);
    hold off;
end