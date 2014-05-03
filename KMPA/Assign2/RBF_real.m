function [w,bestM,bestLamda,bestW,bestCentroid] = RBF_real()
%%
% Regression
% Real World Data
%%
%%Loading Data

filePath = 'F:\Phd\sem2\KM\Assignments\Assignment2\data\data\realworldData\';
trainFile = 'train2.txt';
valFile = 'val2.txt';
testFile= 'test2.txt';


[trainData,trainTarget] = loadData([filePath trainFile]);
[valData,valTarget] = loadData([filePath valFile]);
[testData,testTarget] = loadData([filePath testFile]);

%%
maxM = 40;
minM = 2;
stepM =1;
stepL =1;
maxL = 1;
minL = -40;

logL=minL:stepL:maxL;
complexities=minM:stepM:maxM;
lamdas = [0 exp(logL)];
nLamdas=size(lamdas,2);
nM = size(complexities,2);

weights = cell(nM,nLamdas);
centroids = cell(1,nM);
trainErr = zeros(nM,nLamdas);
valErr = zeros(nM,nLamdas);
testErr = zeros(nM,nLamdas);


s=150;

%Training for different M and lamda

for m = 1:nM
    %'emptyaction','singleton'
    [~,Kmeans] = kmeans(trainData,complexities(m),'replicates',10);
    centroids{m} = Kmeans;
    for l = 1:nLamdas
        %lamda=0;
        [w,trainError] = computeWeight(trainData,trainTarget,complexities(m),Kmeans,lamdas(l),s);
        weights{m,l} = w;
        trainErr(m,l)=trainError;
        valErr(m,l) = computeError(valData,valTarget,w,Kmeans,s);
        testErr(m,l) = computeError(testData,testTarget,w,Kmeans,s);
    end
end


%%
%Find min error
minErr = min(min(valErr));
[r,c]=find(valErr==minErr,1);
bestM=complexities(1,r);
bestCentroid = centroids{r};

bestW = weights{r,c};


str = sprintf('Least Error = %e',minErr);
disp(str);
str = sprintf('Least Erms = %e',sqrt(minErr/size(valData,1)));
disp(str);
str = sprintf('M = %d',bestM);
disp(str);
if c >1
    bestLamda=lamdas(c-1);
    str = sprintf('log(lamda) = %d and lamda = %e',logL(c),bestLamda);
    disp(str);
    str=sprintf('with M=%d ln(lamda)=%d',bestM,logL(c));
else
    bestLamda=0;
    str = sprintf('lamda = %d',bestLamda);
    disp(str);
    str=sprintf('with M=%d lamda=0',bestM);
end

fprintf('Error on Test Data with best model\n');
fprintf('Error = %e\n',testErr(r,c));
fprintf('Erms = %e\n',sqrt(testErr(r,c)/size(testData,1)));


%%
% Plot Erms train,val,test data for diff M,lamda
figure;
hold on;
plot(sqrt(trainErr(:,1)'./size(trainData,1)),'r');
plot(sqrt(valErr(:,1)'./size(valData,1)),'g');
plot(sqrt(testErr(:,1)'./size(testData,1)),'b');
legend('Erms Train','Erms Validation','Erms Test');
title('Erms vs M');
xlabel('M');
ylabel('Erms');
hold off;


figure;
hold on;
plot(logL,sqrt(trainErr(r,2:end)./size(trainData,1)),'r');
plot(logL,sqrt(valErr(r,2:end)'./size(valData,1)),'g');
plot(logL,sqrt(testErr(r,2:end)'./size(testData,1)),'b');
legend('Erms Train','Erms Validation','Erms Test');
title('Erms vs lamda');
xlabel('ln(lamda)');
ylabel('Erms');
hold off;

%%
%plot scatter


phi = designMat(trainData ,bestM,bestCentroid,s);
y = phi*bestW;
figure;
scatter(trainTarget,y,'r*');
xlabel('Target')
ylabel('Model o/p');
hold on;
title(['Scatter plot (train data)' str]);
maxx=max(max(y));
minx=min(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
axis([minx,maxx,minx,maxx]);
hold off;

phi = designMat(valData ,bestM,bestCentroid,s);
y = phi*bestW;
figure;
scatter(valTarget,y,'g*');
hold on;
title(['Scatter plot (validation data)' str]);
xlabel('Target')
ylabel('Model o/p');
maxx=max(max(y));
minx=min(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
axis([minx,maxx,minx,maxx]);
hold off;

phi = designMat(testData ,bestM,bestCentroid,s);
y = phi*bestW;
figure;
scatter(testTarget,y,'b*');
hold on;
title(['Scatter plot (test data)' str]);
xlabel('Target')
ylabel('Model o/p');
maxx=max(max(y));
minx=min(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
axis([minx,maxx,minx,maxx]);
hold off;

end

%%
function phi = designMat(data,complexity,Kmeans,s)
if (nargin<4)
    s = mean(var(data));
end
N = size(data,1);
phi = zeros(N,complexity);

for i = 1:complexity
    X = bsxfun(@minus ,data,Kmeans(i,:));
    X = exp(-sum(X.^2,2)./(2*s));
    phi(:,i)=X;
end
end


function phi = designMatilda(Kmeans,complexity,s)
if (nargin<3)
    s = mean(var(Kmeans));
end
phi = zeros(complexity);
for i = 1:complexity
    X = bsxfun(@minus ,Kmeans,Kmeans(i,:));
    %s=mean(var(X));
    X = exp(-sum(X.^2,2)./(2*s));
    phi(:,i)=X;
end

end

%%
function [error] = computeError(data,target,weight,Kmeans,s)
M = size(weight,1);
if(nargin ~=5)
    phi = designMat(data , M,Kmeans );
else
    phi = designMat(data , M,Kmeans,s);
end

y = phi*weight;
error = (sum((y - target).^2));
%

end
%%


function [w,trainError] = computeWeight(data, target,complexity,Kmeans,lamda,s)
if (nargin==6)
    phi = designMat(data , complexity,Kmeans ,s);
else
    phi = designMat(data , complexity,Kmeans );
     
end
%phitilda=designMatilda(Kmeans,complexity);

w = ((lamda *eye(complexity) ) + phi'*phi)\(phi'*target);%phitilda
y = phi*w;
trainError = (sum((y - target).^2));

end
%%
function [data,target] = loadData(filename)

dataset = load(filename);
[~,ind] = sort(dataset(:,1));
dataset = dataset(ind,:);

data = dataset(:,1:19);
target = dataset(:,20);
end
 