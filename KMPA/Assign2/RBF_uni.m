function  RBF_uni()
%function UniDataSet()
%% Complete Problem on Univariate Dataset

% Polynomial Curve Fitting on Univariate Dataset
% f(x) = exp(cos(2*pi*x))+log(x)+e;
% x : (0,1)

% %% Paths of Dataset
% 
filePath = 'F:\Phd\sem2\KM\Assignments\Assignment2\data\data\univariateData\';

fileTrain1 = 'data.train.1000';
fileTrain2 = 'data.train.100';
fileTrain3 = 'data.train.10';
% % 
fileVal = 'data.val.200';
fileTest = 'data.test.200';

%% Loading of the Data

[trainData1,trainTarget1] = loaD([filePath fileTrain1]);
[trainData2,trainTarget2] = loaD([filePath fileTrain2]);
[trainData3,trainTarget3] = loaD([filePath fileTrain3]);
[valData,valTarget] = loaD([filePath fileVal]);
[testData,testTarget] = loaD([filePath fileTest]);

%% Plot the Data with Function

% plotD(trainData1,trainTarget1,fileTrain1);
% plotD(trainData2,trainTarget2,fileTrain2);
% plotD(trainData3,trainTarget3,fileTrain3);
% plotD(valData,valTarget,fileVal);
% plotD(testData,testTarget,fileTest);

%% Input Model Complexity and Regularization Parameter

% Minimum and Maximum values of M and L
minM = 1; maxM = 50;
minL = -40; maxL = 10;
stepM=1;
% Value and Number of Lamda
lamdas = [0 exp(minL:maxL)];
nLamdas=size(lamdas,2);
complexities=minM:stepM:maxM;

%% Variables for Weights and Errors

weights = cell(maxM,nLamdas);
trainErr = zeros(maxM,nLamdas);
valErr = zeros(maxM,nLamdas);
testErr = zeros(maxM,nLamdas);
trainErms = zeros(maxM,nLamdas);
valErms = zeros(maxM,nLamdas);
testErms = zeros(maxM,nLamdas);

%% Select the Training Dataset

trainData = trainData1;
trainTarget = trainTarget1;
% trainData = Data(:,1);
% trainTarget = Data(:,2);

%% Cross Validate the Weight for diff M and L on Training data

N = size(trainData,1);
for M = minM:maxM
    for l = 1:nLamdas
        [w,trainError] = compW(trainData,trainTarget,M,lamdas(l));
        weights{M,l} = w;
        trainErr(M,l) = trainError;
        trainErms(M,l) = 2*trainError/N;
    end
end

%% Plot Approximated functions using diff M and L

minIndM = 1; maxIndM = maxM;
minIndL = 1; maxIndL = nLamdas;
x = 0:0.001:1;
% figure;
% hold on;
% for M = minIndM:2:maxIndM
%     for l = minIndL:6:maxIndL
%         plotF(weights{M,l});
%     end
% end
% t = exp(cos(2*pi*x))+log(x);
% plot(x,t,'r','linewidth',1.1);
% title('Approximated Functions(blue lines) and Target Function (red line) for diff values of M and L','fontsize',15);
% xlabel('Value of X','fontsize',15);
% ylabel('Value of F(X)','fontsize',15);
% hold off;

%% Find Bias^2, Variance, Avg Loss Function and Error on Validation Data and Plot

% minIndM = 1; maxIndM = maxM;
% minIndL = 1; maxIndL = nLamdas;
% 
% Error = zeros(maxIndM,maxIndL);
% N = size(valData,1);
% y = cell(maxIndM,maxIndL);
% sumY = zeros(N,1);
% for M = minIndM:maxIndM
%     for l = minIndL:maxIndL
%         [Y,Error(M,l)] = retY(weights{M,l},valData,valTarget);
%         sumY = sumY + Y;
%         y{M,l} = Y;
%     end
% end
% 
% Err = sqrt(2*(sum(Error)/maxIndM)/N);
% bias = zeros(1,maxIndL);
% variance = zeros(1,maxIndL);
% avgX = zeros(N,maxIndL);
% for l = minIndL:maxIndL
%     sumX = zeros(N,1);
%     for M = minIndM:maxIndM
%         sumX = sumX + y{M,l};
%     end
%     % Average Approximated function
%     avgX(:,l) = sumX/maxIndM;
%     % Bias^2
%     bias(l) = sum((avgX(l) - valTarget).^2)/N;
%     % Variance
%     varX = zeros(N,1);
%     for M = minIndM:maxIndM
%         varX = varX + (y{M,l}-avgX(l)).^2;
%     end
%     varX = varX/maxIndM;
% %    variance(l) = sum(varX)/N;
% end
% 
% m = bias + variance;
% figure;
% plot(bias);
% hold on;
% plot(variance);
% plot(lamdas,m);
% plot(lamdas,Err);
% legend('Bias','Variance','Bias + Variance','Error','Location','NorthWest');
% title('Bias, Variance, Bias + Variance, Error','fontsize',15);
% xlabel('lamda','fontsize',15);
% ylabel('Value','fontsize',15);
% hold off;

%% Print the min Error on the Train Set

[val, ind] = min(reshape(trainErms, numel(trainErms), 1));
[i,j] = ind2sub(size(trainErms), ind);
disp('Error on Train Set');
str = sprintf('Least Error = %f',trainErr(i,j));
disp(str);
str = sprintf('Least MSE = %f',val);
disp(str);
str = sprintf('M = %f',i);
disp(str);
str = sprintf('index of lamda = %f, log lamda = %f\n',j,log(lamdas(j)));
disp(str);

%% Find the value of M and L for which Error is minimum using Validation data and Select respective Weights for testing

N = size(valData,1);
for M = minM:maxM
    for l = 1:nLamdas
        weight = weights{M,l};
        phi = dMat(valData,M);
        y = phi*weight;
        valError = (sum((y - valTarget).^2));
        valErr(M,l) = valError;
        valErms(M,l) = sqrt(2*valError/N);
    end
end

%% Find optimal M and L

[val, ind] = min(reshape(valErms, numel(valErms), 1));
[i,j] = ind2sub(size(valErms), ind);
disp('Error on Validation Set');
str = sprintf('Least Error = %f',valErr(i,j));
disp(str);
str = sprintf('Least MSE = %f',val);
disp(str);
str = sprintf('M = %f',i);
disp(str);
str = sprintf('index of lamda = %f, log lamda = %f\n',j,log(lamdas(j)));
disp(str);

%% Find Error on Test Data

N = size(testData,1);
for M = minM:maxM
    for l = 1:nLamdas
        weight = weights{M,l};
        phi = dMat(testData,M);
        y = phi*weight;
        testError = (sum((y - testTarget).^2));
        testErr(M,l) = testError;
        testErms(M,l) = sqrt(2*testError/N);
    end
end

%% Print Minimum Error on Test and for the Optimum M and L

[val, ind] = min(reshape(testErms, numel(testErms), 1));
[p,q] = ind2sub(size(testErms), ind);
disp('Error on Test Set');
str = sprintf('Least Error = %f',testErr(p,q));
disp(str);
str = sprintf('Least MSE = %f',val);
disp(str);
str = sprintf('M = %f',p);
disp(str);
str = sprintf('index of lamda = %f, log lamda = %f\n',q,log(lamdas(q)));
disp(str);

% Minimum Error based on the M and L obtained from Validation Data

disp('Error on Test based on M and L form Validation Set');
str = sprintf('Least Error = %f',testErr(i,j));
disp(str);
str = sprintf('Least MSE = %f',val);
disp(str);
str = sprintf('M = %f',i);
disp(str);
str = sprintf('index of lamda = %f, log lamda = %f',j,log(lamdas(j)));
disp(str);

%% Plot the MSE
% 
% minM = 1; maxM = 50;
% minL = -50; maxL = 0;

M = i;
l = j;

% %Value and Number of Lamda
% for M = minM:maxM
%     figure;
%     hold on;
%     plotE(minL,maxL,M,lamdas,trainErms,valErms,testErms);
%     str = sprintf('MSE on Train (blue), Validation (red) and Test data (green) for diff values of L and M = %f', M );
%     title(str);
%     xlabel('log lamda');
%     ylabel('Error-MSE');
%     hold off;
% end

% for l = 1:nLamdas
%     figure;
%     hold on;
%     plotM(l,maxM,trainErms,valErms,testErms);
%     str = sprintf('MSE on Train (blue), Validation (red) and Test data (green) for diff values of M and log L = %f', log(lamdas(l)));
%     title(str);
%     xlabel('Model Complexity, M');
%     ylabel('Error-MSE');
%     hold off;
%  end

%% Model o/p vs Target o/p plot

minIndM = 1; maxIndM = maxM;
minIndL = 1; maxIndL = nLamdas;
x = 0:0.001:1;
t = exp(cos(2*pi*x))+log(x);
yTrain = cell(maxIndM,maxIndL);
yVal = cell(maxIndM,maxIndL);
yTest = cell(maxIndM,maxIndL);

x = 0:0.001:1;
M = 13;
l = 9;

% for M = minIndM:maxIndM
%    for l = minIndL:maxIndL
        [X,Y,Z] = retMO(weights{M,l},trainData,valData,testData);
        yTrain{M,l} = X;
        yVal{M,l} = Y;
        yTest{M,l} = Z;
% 
        figure;
        %stem(trainTarget,X);
%         t = exp(cos(2*pi*x))+log(x);
%         plot(x,t,'k');
        hold on;
        plot(trainData,trainTarget,'linewidth',1.1);
        plot(trainData,X,'r','linewidth',1.1);
        legend('Target','Train(Model o/p)','Location','NorthWest');
        str = sprintf('Model output Vs Target output for M = %f and log Lamda = %f',M,log(lamdas(l)));
        title(str);
        xlabel('Value of X');
        ylabel('Value of F(X)');
        hold off;

        figure;
        %stem(valTarget,Y);
%         t = exp(cos(2*pi*x))+log(x);
%         plot(x,t,'k','linewidth',1.1);
        hold on;
        plot(valData,valTarget,'linewidth',1.1);
        plot(valData,Y,'r','linewidth',1.1);
        legend('Target','Validation(Model o/p)','Location','NorthWest');
        str = sprintf('Model output Vs Target output for M = %f and log Lamda = %f',M,log(lamdas(l)));
        title(str);
        xlabel('Value of X');
        ylabel('Value of F(X)');
        hold off;

        figure;
        %stem(testTarget,Z);
%         t = exp(cos(2*pi*x))+log(x);
%         plot(x,t,'k','linewidth',1.1);
        hold on;
        plot(testData,testTarget,'linewidth',1.1);
        plot(testData,Z,'r','linewidth',1.1);
        legend('Target','Test(Model o/p)','Location','NorthWest');
        str = sprintf('Model output Vs Target output for M = %f and log Lamda = %f',M,log(lamdas(l)));
        title(str);
        xlabel('Value of X');
        ylabel('Value of F(X)');
        hold off;

%% Target v/s Model o/p

        figure;
        %stem(trainTarget,X);
        scatter(trainTarget,X,'r');
        hold on;
        maxX = max(X);
        minX = min(X);
        linx = linspace(minX,maxX,101);
        plot(linx,linx,'m','linewidth',2);
        legend('Target Vs Model o/p(Train)','Location','NorthWest');
        str = sprintf('Model output Vs Target output for M = %f and log Lamda = %f',M,log(lamdas(l)));
        title(str);
        xlabel('Target');
        ylabel('Model');
        hold off;

        figure;
        %stem(trainTarget,X);
        scatter(valTarget,Y,'r');
        hold on;
        maxY = max(Y);
        minY = min(Y);
        liny = linspace(minY,maxY,101);
        plot(liny,liny,'m','linewidth',2);
        legend('Target Vs Model o/p(Validation)','Location','NorthWest');
        str = sprintf('Model output Vs Target output for M = %f and log Lamda = %f',M,log(lamdas(l)));
        title(str);
        xlabel('Target');
        ylabel('Model');
        hold off;

        figure;
        %stem(trainTarget,X);
        scatter(testTarget,Z,'r');
        hold on;
        maxZ = max(Z);
        minZ = min(Z);
        linz = linspace(minZ,maxZ,101);
        plot(linz,linz,'m','linewidth',2);
        legend('Target Vs Model o/p(Test)','Location','NorthWest');
        str = sprintf('Model output Vs Target output for M = %f and log Lamda = %f',M,log(lamdas(l)));
        title(str);
        xlabel('Target');
        ylabel('Model');
        hold off;
%    end
% end

%%
end

%% Functions used for Polynomial Curve Fitting

%% Function used for Loading Data

function [data,target] = loaD(filename)
% Load data
dataset = load(filename);
% Sort the dataset
[~,ind] = sort(dataset(:,1));
dataset = dataset(ind,:);
% Divide dataset into data and target
data = dataset(:,1);
target = dataset(:,2);
end

%% Function for Ploting Data with Function

function plotD(data,target,filename)
% Generating target values of function
x = 0:.001:1;
t = exp(cos(2*pi*x))+log(x);
% Ploting the data
figure;
scatter(data,target,36,'r');
hold on;
plot(x,t,'linewidth',1.1);
legend([filename ' Dataset'],'Function F(X)','Location','NorthWest');
title(['Univarite Dataset: (' filename ') Function(blue line) and Dataset (red dots) with Gaussian noise'],'fontsize',15);
xlabel('Value of X');
ylabel('Value of F(X)');
hold off;
end

%% Function for Computing the Weights for diff values of M and L

function [w,trainError] = compW(data, target,complexity,lamda)
phi = dMat(data,complexity);
phitilda = dMatilda(data,complexity);
warning off;
w = ((lamda * phitilda) + phi'*phi)\(phi'*target);
y = phi*w;
trainError = (sum((y - target).^2));
end

%% Function for creating Design Matrix

function phi = dMat(data,complexity)
phi = bsxfun(@power , data , (0:complexity-1));
end
%% Function for creating Design Matrix

function phitilda = dMatilda(trainData,complexity)

[~,Kmeans] = kmeans(trainData,complexity);
phi = bsxfun(@minus , Kmeans , Kmeans);
s=max(phi)/2*complexity;
phi=power(norm(phi),2)/2*s;
phitilda=exp(phi);
end


%% Function to plot Approximated functions

function plotF(weight)
x = 0:0.001:1;
M = size(weight,1);
phi = dMat(x',M);
y = phi*weight;
plot(x,y);
end

% %% Function to Calculate y for calculating Bias^2, Variance and Average Loss Function
% 
% function [y,Error] = retY(weight,valData,valTarget)
% yD = valData;
% M = size(weight,1);
% phi = dMat(yD,M);
% y = phi*weight;
% Error = (sum((y - valTarget).^2));
% end

%% Function to plot Error vs ln lamda

function plotE(minL,maxL,M,l,trainErms,valErms,testErms)
n = minL:1:(maxL+1);
train = trainErms(M,:);
val = valErms(M,:);
test = testErms(M,:);
plot(n,train,'b');
plot(n,val,'r');
plot(n,test,'g');

legend('Train','Validation','Test','Location','NorthWest');
end

%% Function to plot Error vs M

function plotM(l,M,trainErms,valErms,testErms)
train = trainErms(:,l);
val = valErms(:,l);
test = testErms(:,l);
plot(train);
plot(val,'r');
plot(test,'g');
legend('Train','Validation','Test','Location','NorthWest');
end

%% Function to Calculate Model output

function [x,y,z] = retMO(weight,trainData,valData,testData)
xD = trainData;
yD = valData;
zD = testData;
M = size(weight,1);
xphi = dMat(xD,M);
yphi = dMat(yD,M);
zphi = dMat(zD,M);
x = xphi*weight;
y = yphi*weight;
z = zphi*weight;
end

%%
