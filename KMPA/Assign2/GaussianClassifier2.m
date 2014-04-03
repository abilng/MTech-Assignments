

function GaussianClassifier2(DataRoot,K,MaxM)
%
%Gaussian Classifier : Function to train a system to classify a given element to any
%of the classes using GMM Classifier; and to find the
%Classification Accuracy, Confusion Matrix and Decision Region Plot of the
%classifier.
%
%Input
%DataRoot - Path to a folder containing the data.
%K - No of Class
%MaxM - Maxium number of Cluster

%Description

%{
class1_test.txt   class2_test.txt   class3_test.txt
class1_train.txt  class2_train.txt  class3_train.txt
class1_val.txt    class2_val.txt    class3_val.txt
%}

%Loading the Data

TrainData= cell(1,K);
TestData = cell(1,K);
ValData  = cell(1,K);
for i=1:K
    TrainData{i} = load(strcat(DataRoot,'/class',int2str(i),'_train.txt'));
    TestData{i} = load(strcat(DataRoot,'/class',int2str(i),'_test.txt'));
    ValData{i} = load(strcat(DataRoot,'/class',int2str(i),'_val.txt'));
end

dim=size(TrainData{1},2);

gmm=cell(MaxM,K);
ErrorRate = zeros(1,MaxM);

for M = 1:MaxM
    %estimateing the Class
    for i=1:K
        %gmm{M,i}= gmdistribution.fit(TrainData{i},M);
        gmm{M,i}= gmdistribution.fit(TrainData{i},M,'Regularize',1e-2);
    end
    for i=1:K
        label = getClass(ValData{i},gmm(M,:));
        ErrorRate(M)=ErrorRate(M)+sum(label~=i);
    end
end
%Classification Accuracy
ErrorRate=ErrorRate/K;
[~,best]=min(ErrorRate);

figure;
plot(ErrorRate)
xlabel('No of Clusters');
ylabel('Avg Misclassification')


%Finding the Decision Regions
if dim == 2
%    for i=1:MaxM
    plotClassifer(TrainData,ValData,TestData,gmm(best,:),K);
    title(['Decision Boundaries - Bayes classifier ', ...
        '(Gaussian Mixure model) No of Clusters = ',int2str(best)]);
    hold off;
%    end
end


%Confusion Matrix
ConfMat(1:K,1:K) = 0;
%Classification Accuracy
Accu(1:K) = 0;
for i = 1:K
        classlabel = getClass(TestData{i},gmm(best,:));
        for j=1:K
            ConfMat(i,j) = ConfMat(i,j) + sum(classlabel==j);    
        end
Accu(i) = ConfMat(i,i) / sum(ConfMat(i,:));        
end
disp(['Best Model: No of Clusters = ',int2str(best)]);
disp('Confusion Matrix');
disp(ConfMat);
disp('Classification Accuracy');
disp(Accu);

disp('Average Accuracy');
disp(mean(Accu));

end


function class = getClass( X, gmms)

%{

GETCLASS : Function to find, X belongs to which Class.

Input
X - Element to be classified.
gmm objects

Output
class - Class of the element X.

Decription


%}

K = size(gmms,2);
N = size(X,1);
g = zeros(K,N);
for i=1:K
    g(i,:) = log(pdf(gmms{i},X));
end
[~,class] = max(g);

end

function plotClassifer(TrainData,ValData,TestData,gmms,K)
%{

PLOTCLASSIFIER - Function to plot the data and decision boundaries.
ClassA,ClassB,ClassC - Tarin data
gA,gB,gC - handle to decision surface
%}

cmap = hsv(K+3);

figure;

class = [cell2mat(TrainData'); cell2mat(ValData'); ...
    cell2mat(TestData');];
xmin = min(class(:,1)) - 5;
xmax = max(class(:,1)) + 5;
ymin = min(class(:,2)) - 5;
ymax = max(class(:,2)) + 5;

hold on;
for i = 1:K
    scatter(TrainData{i}(:,1),TrainData{i}(:,2),'d','filled','MarkerFaceColor',cmap(i,:));
    scatter(ValData{i}(:,1),ValData{i}(:,2),'d','filled','MarkerFaceColor',cmap(i,:));
    scatter(TestData{i}(:,1),TestData{i}(:,2),'d','filled','MarkerFaceColor',cmap(i,:));
end

s = warning('off','all');

for i = 1:K
    syms x y;
    g= @(x,y) log(pdf(gmms{i},[x,y]));
    gplot = ezsurf(g,[xmin,xmax,ymin,ymax]);
    set(gplot, 'FaceColor', [1 1 1]-cmap(i,:));
end
warning(s);

xlabel('x');
ylabel('y');


end
