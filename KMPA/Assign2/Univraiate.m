function Univraiate()
%%
% Regression
% 
%
%Loading Data

filePath = '../data/univariateData/';
% 
%fileTrain = 'data.train.1000';
fileTrain = 'data.train.100';
%fileTrain = 'data.train.10';
% % 
fileVal = 'data.val.200';
fileTest = 'data.test.200';

[trainData,trainTarget] = loadData([filePath fileTrain]);
[valData,valTarget] = loadData([filePath fileVal]);
[testData,testTarget] = loadData([filePath fileTest]);

TrainSize=size(trainData,1);
TestSize=size(testData,1);
ValSize=size(valData,1);


inputs = [trainData;valData;testData]';
targets = [trainTarget;valTarget;testTarget]';

%dim=size(AllTrainData,2);

maxM = 15;
minM = 1;
stepM =1;
hiddenLayerSizes = minM:stepM:maxM;

net = cell(size(hiddenLayerSizes));

trainPerformance = zeros(size(hiddenLayerSizes));
valPerformance = zeros(size(hiddenLayerSizes));
testPerformance = zeros(size(hiddenLayerSizes));
%%
% Create a Fitting Network
for i =1:size(hiddenLayerSizes,2)
%hiddenLayerSize = 10;
net{i} = fitnet(hiddenLayerSizes(i));

% Choose Input and Output Pre/Post-Processing Functions
% For a list of all processing functions type: help nnprocess
net{i}.inputs{1}.processFcns = {'removeconstantrows','mapminmax'};
net{i}.outputs{2}.processFcns = {'removeconstantrows','mapminmax'};


% Setup Division of Data for Training, Validation, Testing
% For a list of all data division functions type: help nndivide
net{i}.divideFcn = 'divideind';
net{i}.divideMode = 'sample';  % Divide up every sample
net{i}.divideParam.trainInd = 1:TrainSize;
net{i}.divideParam.valInd = TrainSize+1:TrainSize+ValSize;
net{i}.divideParam.testInd = TrainSize+ValSize+1:TrainSize+ValSize+TestSize;

% For help on training function 'trainlm' type: help trainlm
% For a list of all training functions type: help nntrain

net{i}.trainFcn = 'traingdx';  %
net{i}.trainParam.epochs=4000;
net{i}.trainParam.min_grad=1e-6;
net{i}.trainParam.max_fail = 1000;
net{i}.trainParam.lr=0.1;
net{i}.trainParam.mc=0.9;
net{i}.layers{1}.transferFcn = 'tansig';%tansig%purelin%logsig
net{i}.layers{2}.transferFcn = 'purelin';


% Choose a Performance Function
% For a list of all performance functions type: help nnperformance
net{i}.performFcn = 'mse';  % Mean squared error

% Choose Plot Functions
% For a list of all plot functions type: help nnplot
net{i}.plotFcns = {'plotperform','plottrainstate','ploterrhist', ...
  'plotregression', 'plotfit'};


% Train the Network
[net{i},tr] = train(net{i},inputs,targets);

% Test the Network
outputs = net{i}(inputs);
%errors = gsubtract(targets,outputs);
%performance = perform(net{i},targets,outputs)

% Recalculate Training, Validation and Test Performance
trainTargets = targets .* tr.trainMask{1};
valTargets = targets  .* tr.valMask{1};
testTargets = targets  .* tr.testMask{1};
trainPerformance(i) = perform(net{i},trainTargets,outputs);
valPerformance(i) = perform(net{i},valTargets,outputs);
testPerformance(i) = perform(net{i},testTargets,outputs);
end


figure;
hold on;
plot(hiddenLayerSizes,trainPerformance,'r');
plot(hiddenLayerSizes,valPerformance,'g');
plot(hiddenLayerSizes,testPerformance,'b');
ylabel('MSError');
xlabel('No of Hidden layers');
legend('Train Data','Validation Data','Test Data');

bestPerformance = min(valPerformance);
r=find(valPerformance==bestPerformance,1);
bestNet = net{r};

% View the Network
view(bestNet);

% Plots
% Uncomment these lines to enable various plots.
%figure, plotperform(tr)
%figure, plottrainstate(tr)

figure, plotfit(bestNet,trainData',trainTarget','Train Data Set')
figure, plotfit(bestNet,testData',testTarget','Test Data Set')
figure, plotfit(bestNet,valData',valTarget','validation Data Set')


str=sprintf(' with No of Hidden Layer=%d',hiddenLayerSizes(r));
 
y = bestNet(trainData');
figure;
scatter(trainTarget,y','r*');
xlabel('Target')
ylabel('Model o/p');
hold on;
title(['Scatter plot (Train data)' str]);
maxx=(max(y));
minx=(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
hold off;


y = bestNet(valData');
figure;
scatter(valTarget,y','g*');
hold on;
title(['Scatter plot (validation data)' str]);
xlabel('Target')
ylabel('Model o/p');
maxx=max(y);
minx=(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
hold off;

y = bestNet(testData');
figure;
scatter(testTarget,y','b*');
hold on;
title(['Scatter plot (test data)' str]);
xlabel('Target')
ylabel('Model o/p');
maxx=(max(y));
minx=(min(y));
x=linspace(minx,maxx,101);
plot(x,x,'m','LineWidth',2);
hold off;


end
%%


function [data,target] = loadData(filename)

dataset = load(filename);
data = dataset(:,1:(end-1));
target = dataset(:,end);
end

