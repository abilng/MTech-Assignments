function [net,trainPerformance,valPerformance,testPerformance]= MLFFNN(DataRoot,K,M,dividerand)
%MLFFNN Summary of this function goes here
%   Detailed explanation goes here

if nargin < 4
    dividerand = false;
end

AllTrainData= [];
AllTestData = [];
AllValData  = [];

AllTrainLabel= [];
AllTestLabel = [];
AllValLabel  = [];

for i=1:K
    TrainData = load(strcat(DataRoot,'/class',int2str(i),'_train.txt'));
    TrainLabel = zeros(size(TrainData,1),K);
    TrainLabel(:,i) = 1;
    TestData = load(strcat(DataRoot,'/class',int2str(i),'_test.txt'));
    TestLabel = zeros(size(TestData,1),K);
    TestLabel(:,i) = 1;
    ValData = load(strcat(DataRoot,'/class',int2str(i),'_val.txt'));
    ValLabel = zeros(size(ValData,1),K);
    ValLabel(:,i) = 1;
    
    AllTrainData = [AllTrainData;TrainData];
    AllValData = [AllValData;ValData];
    AllTestData = [AllTestData;TestData];
    
    AllTrainLabel = [AllTrainLabel;TrainLabel];
    AllValLabel = [AllValLabel;ValLabel];
    AllTestLabel = [AllTestLabel;TestLabel];
    
end

TrainSize=size(AllTrainData,1);
TestSize=size(AllTestData,1);
ValSize=size(AllValData,1);

dim=size(AllTrainData,2);

%{
%Mixing of Data
index = randperm(TrainSize);
AllTrainData = AllTrainData(index,:);
AllTrainLabel = AllTrainLabel(index,:);

index = randperm(TestSize);
AllTestData = AllTestData(index,:);
AllTestLabel = AllTestLabel(index,:);

index = randperm(ValSize);
AllValData = AllValData(index,:);
AllValLabel = AllValLabel(index,:);
%}

inputs = [AllTrainData;AllValData;AllTestData]';
targets = [AllTrainLabel;AllValLabel;AllTestLabel]';

% Create a Pattern Recognition Network
hiddenLayerSize = M;
net = patternnet(hiddenLayerSize);

% Choose Input and Output Pre/Post-Processing Functions
% For a list of all processing functions type: help nnprocess
net.inputs{1}.processFcns = {'removeconstantrows','mapminmax'};
net.outputs{2}.processFcns = {'removeconstantrows','mapminmax'};


% Setup Division of Data for Training, Validation, Testing
% For a list of all data division functions type: help nndivide
if dividerand
   net.divideFcn = 'dividerand';
   net.divideParam.trainRatio = 0.7;
   net.divideParam.valRatio = 0.1;
   net.divideParam.testRatio = 0.2; 
else
    net.divideFcn = 'divideind';
    net.divideMode = 'sample';  % Divide up every sample
    net.divideParam.trainInd = 1:TrainSize;
    net.divideParam.valInd = TrainSize+1:TrainSize+ValSize;
    net.divideParam.testInd = TrainSize+ValSize+1:TrainSize+ValSize+TestSize;
end
% For help on training function 'trainlm' type: help trainlm
% For a list of all training functions type: help nntrain
net.trainFcn = 'traingdx';  % Gradient descent with momentum and adaptive learning rate backpropagation

% Choose a Performance Function
% For a list of all performance functions type: help nnperformance
net.performFcn = 'mse';  % Mean squared error


%
net.trainParam.epochs=2000;
net.trainParam.min_grad=1e-6;
net.trainParam.lr=0.1;
net.trainParam.mc=0.9;
net.layers{1}.transferFcn = 'tansig';%tansig%purelin%logsig
net.layers{2}.transferFcn = 'tansig';


% Choose Plot Functions
% For a list of all plot functions type: help nnplot
net.plotFcns = {'plotperform','plottrainstate','ploterrhist', ...
    'plotregression', 'plotfit','plotconfusion','plotroc'};


% Train the Network
[net,tr] = train(net,inputs,targets);

% Test the Network
outputs = net(inputs);
%errors = gsubtract(targets,outputs);
%performance = perform(net,targets,outputs)

% Recalculate Training, Validation and Test Performance
trainTargets = targets .* tr.trainMask{1};
valTargets = targets  .* tr.valMask{1};
testTargets = targets  .* tr.testMask{1};
trainPerformance = perform(net,trainTargets,outputs);
valPerformance = perform(net,valTargets,outputs);
testPerformance = perform(net,testTargets,outputs);

% View the Network
view(net)

% Plots
% Uncomment these lines to enable various plots.
%figure, plotperform(tr)
%figure, plottrainstate(tr)
figure, plotconfusion(testTargets,outputs)
%figure, ploterrhist(errors)
if dim == 2
    plotClassifer(inputs,targets,net,K)
end
end


function [Z] = decisionSurf(X,Y,class,net)
output=net([X,Y]');
Z=output(class,:);
end


function plotClassifer(AllData,AllLabel,net,K)
%{

PLOTCLASSIFIER - Function to plot the data and decision boundaries.
ClassA,ClassB,ClassC - Tarin data
gA,gB,gC - handle to decision surface
%}

cmap = hsv(K+3);

figure;

xmin = min(AllData(1,:)) - 5;
xmax = max(AllData(1,:)) + 5;
ymin = min(AllData(2,:)) - 5;
ymax = max(AllData(2,:)) + 5;


hold on;
for i = 1:K
    ClassData = AllData(:,AllLabel(i,:)==1);
    scatter3(ClassData(1,:),ClassData(2,:),ones(1,size(ClassData,2)), ...
        'd','filled','MarkerFaceColor',cmap(i,:));
end

s = warning('off','all');

for i = 1:K
    syms x y;
    g = @(x,y)(decisionSurf(x,y,i,net));
    gplot = ezsurf(g,[xmin,xmax,ymin,ymax]);
    set(gplot, 'FaceColor', [1 1 1]-cmap(i,:));
    hold on;
end
warning(s);

xlabel('x');
ylabel('y');

end