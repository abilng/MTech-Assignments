
function classifier(DataRoot,K,NaiveBayes)
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

TrainData= cell(1,K);
TestData = cell(1,K);
ValData  = cell(1,K);
classMean= cell(1,K);
classVar = cell(1,K);
classSize = zeros(1,K);
for i=1:K
    TrainData{i} = load(strcat(DataRoot,'/class',int2str(i),'_train.txt'));
    TestData{i} = load(strcat(DataRoot,'/class',int2str(i),'_test.txt'));
    ValData{i} = load(strcat(DataRoot,'/class',int2str(i),'_val.txt'));
    [ classMean{i}, classVar{i}] = estimate(TrainData{i});
    classSize(i)=size(TrainData{i},1);
    if NaiveBayes
        classVar{i} = diag(diag(classVar{i}));
    end
end

dim=size(TrainData{1},2);

prob = classSize./(sum(classSize,2));

%Confusion Matrix
ConfMat(1:K,1:K) = 0;
%Classification Accuracy
Accu(1:K) = 0;
    
%Finding the Decision Regions
for i=1:K
    for p = 1:size(TestData{i},1)
        X = TestData{i}(p,:);
        class = getClass(X, classMean, classVar,prob);
        ConfMat(i,class) = ConfMat(i,class) + 1;    
    end
    Accu(i) = ConfMat(i,i) / sum(ConfMat(i,:));
end
disp('Confusion Matrix');
disp(ConfMat);
disp('Classification Accuracy');
disp(Accu);
disp('Average Accuracy');
disp(mean(Accu));

end


function [classMean, classVar] = estimate(train)
%estimate : find the Mean and Covariance matrices of that Training data.
classMean = mean(train);
classVar = cov(train);
end

function class = getClass( X, means,coVars,piors)

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

K = size(means,2);
g = zeros(K,1);
for i=1:K
    g(i,:) = discriFun( X, means{i}, coVars{i},piors(i));
end
[~,class] = max(g);


end

function g = discriFun( X, M, C,p)

%DISCRI_FUN : Function to find the value of Discriminant Function.

g = -((X-M)/C*(X-M)'+log(abs(det(C))))/2+ p;

end
