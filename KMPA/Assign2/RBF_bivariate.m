function [w,bestM,bestLamda,bestW,bestCentroid] = RBF_old()
%%
% Regression
% Real World Data
%%
%%Loading Data
filePath = 'F:\Phd\sem2\KM\Assignments\Assignment2\data\data\bivariateData\';
trainFile = 'group8_train100.txt';
valFile = 'group8_val.txt';
testFile= 'group8_test.txt';

%{
group8_train.txt
group8_train20.txt 
group8_train100.txt
group8_train1000.txt
%}

[trainData,trainTarget] = loadData([filePath trainFile]);
[valData,valTarget] = loadData([filePath valFile]);
[testData,testTarget] = loadData([filePath testFile]);

%%
maxM = 40;
minM = 3;
stepM =1;
stepL =1;
maxL = 0;
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

s=25;

%Training for different M and lamda

for m = 1:nM
    [~,Kmeans] = kmeans(trainData,complexities(m));
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
str = sprintf('Least MSE = %e',(minErr/size(valData,1)));
disp(str);
fprintf('M = %d\n',bestM);
if c >1
    bestLamda=lamdas(c-1);
    str = sprintf('log(lamda) = %d lamda = %e',logL(c),bestLamda);
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
fprintf('MSE = %e\n',testErr(r,c)/size(testData,1));


%%
% Plot Erms train,val,test data for diff M,lamda
figure;
hold on;
plot((trainErr(:,1)'./size(trainData,1)),'r');
plot((valErr(:,1)'./size(valData,1)),'g');
plot((testErr(:,1)'./size(testData,1)),'b');
legend('MSE Train','MSE Validation','MSE Test');
title('MSE vs M');
xlabel('M');
ylabel('MSE');
hold off;


figure;
hold on;
plot(logL,(trainErr(r,2:end)./size(trainData,1)),'r');
plot(logL,(valErr(r,2:end)'./size(valData,1)),'g');
plot(logL,(testErr(r,2:end)'./size(testData,1)),'b');
legend('MSE Train','MSE Validation','MSE Test');
title('MSE vs lamda');
xlabel('ln(lamda)');
ylabel('MSE');
hold off;

%%
%plot scatter and model/op


phi = designMat(trainData ,bestM,bestCentroid,s);
y = phi*bestW;
figure;
scatter(trainTarget,y,'r*');
xlabel('Target')
ylabel('Model o/p');
hold on;
title(['Scatter plot (Train data)' str]);
maxx=(max(y));
minx=(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
hold off;

%model/op
figure;
hold on;
title(['Model output vs Target output (train data)' str]);
scatter3(trainData(:,1),trainData(:,2),trainTarget,'MarkerFaceColor',[0 .5 .5]);
scatter3(trainData(:,1),trainData(:,2),y,'MarkerFaceColor',[1 0 0]);
legend('Target Output','Model Output');
xlabel('Input variable x1');
ylabel('Input variable x2');
zlabel('Output');
hold off;

phi = designMat(valData ,bestM,bestCentroid,s);
y = phi*bestW;
figure;
scatter(valTarget,y,'g*');
hold on;
title(['Scatter plot (validation data)' str]);
xlabel('Target')
ylabel('Model o/p');
maxx=max(y);
minx=(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
hold off;

%model/op
figure;
hold on;
title(['Model output vs Target output (validation data)' str]);
scatter3(valData(:,1),valData(:,2),valTarget,'MarkerFaceColor',[0 .5 .5]);
scatter3(valData(:,1),valData(:,2),y,'MarkerFaceColor',[1 0 0]);
legend('Target Output','Model Output');
xlabel('Input variable x1');
ylabel('Input variable x2');
%minValX=min(valData);
%maxValX=max(valData);
%[xq,yq] = meshgrid(minValX(1):maxValX(2),minValX(2):maxValX(2));
%vq = griddata(valData(:,1),valData(:,2),valTarget,xq,yq);
%mesh(xq,yq,vq);
zlabel('Output');
hold off;


phi = designMat(testData ,bestM,bestCentroid,s);
y = phi*bestW;
figure;
scatter(testTarget,y,'b*');
hold on;
title(['Scatter plot (test data)' str]);
xlabel('Target')
ylabel('Model o/p');
maxx=(max(y));
minx=(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
hold off;

%model/op
figure;
hold on;
title(['Model output vs Target output  (test data)' str]);
scatter3(testData(:,1),testData(:,2),testTarget,'MarkerFaceColor',[0 .5 .5]);
scatter3(testData(:,1),testData(:,2),y,'MarkerFaceColor',[1 0 0]);
legend('Target Output','Model Output');
xlabel('Input variable x1');
ylabel('Input variable x2');
zlabel('Output');
hold off;


end

%%
function phi = designMat(data,complexity,Kmeans,s)
if (nargin<4)
    s = mean(var(data));
end
N = size(data,1);
phi = zeros(N,complexity-1);

for i = 1:complexity
    X = bsxfun(@minus ,data,Kmeans(i,:));
    phi(:,i) = exp(-sum(X.^2,2)./(2*s));
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
    phitilda=designMatilda(Kmeans,complexity,s);
else
    phi = designMat(data , complexity,Kmeans );
    phitilda=designMatilda(Kmeans,complexity);
end
w = ((lamda * phitilda) + phi'*phi)\(phi'*target);
y = phi*w;
trainError = (sum((y - target).^2));

end
%%
function [data,target] = loadData(filename)

dataset = load(filename);
[~,ind] = sort(dataset(:,1));
dataset = dataset(ind,:);

data = dataset(:,1:2);
target = dataset(:,3);
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
