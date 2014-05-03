function PlotHidden(M)
%%
% Regression
%
%
%Loading Data

filePath = '../data/bivariateData/';
trainFile = 'group8_train1000.txt';
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

TrainSize=size(trainData,1);
TestSize=size(testData,1);
ValSize=size(valData,1);


inputs = [trainData;valData;testData]';
targets = [trainTarget;valTarget;testTarget]';

%dim=size(AllTrainData,2);

epochs = [0:1:3,25,100:250:1000,2000:1000:10000];
%%
% Create a Fitting Network
%hiddenLayerSize = 10;
for i = epochs
    rng('default');
    
    net = fitnet(M);
    
    % Choose Input and Output Pre/Post-Processing Functions
    % For a list of all processing functions type: help nnprocess
    net.inputs{1}.processFcns = {'removeconstantrows','mapminmax'};
    net.outputs{2}.processFcns = {'removeconstantrows','mapminmax'};
    
    
    % Setup Division of Data for Training, Validation, Testing
    % For a list of all data division functions type: help nndivide
    net.divideFcn = 'divideind';
    net.divideMode = 'sample';  % Divide up every sample
    net.divideParam.trainInd = 1:TrainSize;
    net.divideParam.valInd = TrainSize+1:TrainSize+ValSize;
    net.divideParam.testInd = TrainSize+ValSize+1:TrainSize+ValSize+TestSize;
    
    % For help on training function 'trainlm' type: help trainlm
    % For a list of all training functions type: help nntrain

    net.trainFcn = 'traingdx';  %
    net.trainParam.epochs=i;
    net.trainParam.min_grad=1e-6;
    net.trainParam.max_fail = 1000;
    net.trainParam.lr=0.1;
    net.trainParam.mc=0.9;
    net.layers{1}.transferFcn = 'tansig';%tansig%purelin%logsig
    net.layers{2}.transferFcn = 'purelin';
    
    % Choose a Performance Function
    % For a list of all performance functions type: help nnperformance
    net.performFcn = 'mse';  % Mean squared error
    
    % Choose Plot Functions
    % For a list of all plot functions type: help nnplot
    net.plotFcns = {'plotperform','plottrainstate','ploterrhist', ...
        'plotregression', 'plotfit'};
    
    
    % Train the Network
    [net,tr] = train(net,inputs,targets);
    
    % Test the Network
    %outputs = net(inputs);
    %errors = gsubtract(targets,outputs);
    %performance = perform(net,targets,outputs)
    
    % View the Network
    % view(net);
    
    % Plots
    % Uncomment these lines to enable various plots.
    %figure, plotperform(tr)
    %figure, plottrainstate(tr)
    %figure, plotfit(net,inputs,targets)
    %figure, plotregression(targets,outputs)
    %figure, ploterrhist(errors)
    
    disp([ 'After ',int2str(tr.epoch(end)),'epoch']);
    disp('Weigths:')
    disp('Weigths:');disp(net.iw{1});
    disp('bias');disp(net.b{1});
    
    plotHiddenLayer(testData,net,M,tr.epoch(end));
    plotOutputLayer(testData,testTarget,net,M,tr.epoch(end));
end
end
%%

function [Z]=hiddenSurf(X,Y,hiddenLayer,net)
input = [X,Y]';
weigthts = net.iw{1};
bias = net.b{1};
p=weigthts(hiddenLayer,:)*(input);
weightedSum=p+bias(hiddenLayer);
transferFcn = str2func(net.layers{1}.transferFcn);
Z = transferFcn(weightedSum);
end


function plotHiddenLayer(testData,net,M,step)


xmin = min(testData(:,1)) - 0.5;
xmax = max(testData(:,1)) + 0.5;
ymin = min(testData(:,2)) - 0.5;
ymax = max(testData(:,2)) + 0.5;
s = warning('off','all');
for i = 1:M
    h=figure;
    %    scatter3(testData(:,1),testData(:,2),testTarget,'MarkerFaceColor',[0 .5 .5]);
    hold on;
    syms x y;
    g = @(x,y)(hiddenSurf(x,y,i,net));
    ezsurf(g,[xmin,xmax,ymin,ymax]);
    colormap cool
    title(['Output of Hidden Node (', int2str(i),') at epoch =',int2str(step) ])
    view([45 45]);
    saveas(h, ['../output/hiddenLayer' num2str(i) '/epoch_',int2str(step)], 'fig');
    saveas(h, ['../output/hiddenLayer' num2str(i) '/epoch_',int2str(step)], 'png');    
    close(h);
end


warning(s);


xlabel('x');
ylabel('y');

end

function plotOutputLayer(testData,testTarget,net,M,step)
y = net(testData');
h=figure;
hold on;
title(['Output at epoch =',int2str(step) ]);
scatter3(testData(:,1),testData(:,2),testTarget,'MarkerFaceColor',[0 .5 .5]);
scatter3(testData(:,1),testData(:,2),y','MarkerFaceColor',[1 0 0]);
legend('Target Output','Model Output');
xlabel('Input variable x1');
ylabel('Input variable x2');
zlabel('Output');
view([-35,15]);
hold off;
saveas(h, ['../output/outLayer/epoch_',int2str(step)], 'fig');
saveas(h, ['../output/outLayer/epoch_',int2str(step)], 'png');
close(h);
end

function [data,target] = loadData(filename)

dataset = load(filename);
data = dataset(:,1:(end-1));
target = dataset(:,end);
end
