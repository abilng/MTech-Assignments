function [neurons,trainPerformance,valPerformance,testPerformance]= PerceptronFn(DataRoot)
%perceptronFn Summary of this function goes here
%   Detailed explanation goes here




TrainData= cell(1,3);
TestData = cell(1,3);
ValData  = cell(1,3);
for i=1:3
    TrainData{i} = load(strcat(DataRoot,'/class',int2str(i),'_train.txt'));
    TestData{i} = load(strcat(DataRoot,'/class',int2str(i),'_test.txt'));
    ValData{i} = load(strcat(DataRoot,'/class',int2str(i),'_val.txt'));
end

neurons = cell(1,3);
neuronsClasses = {[1,2],[2,3],[3,1]};
trainPerformance = cell(1,3);
valPerformance = cell(1,3);
testPerformance = cell(1,3);


for i = 1:3
    
    a=neuronsClasses{i}(1);
    b=neuronsClasses{i}(2);
    
    AllTrainData = [TrainData{a};TrainData{b}];
    AllValData = [ValData{a};ValData{b}];
    AllTestData = [TestData{a};TestData{b}];
    
    TrainSize=size(AllTrainData,1);
    TestSize=size(AllTestData,1);
    ValSize=size(AllValData,1);

    AllTrainLabel = zeros(TrainSize,1);
    AllValLabel = zeros(ValSize,1);
    AllTestLabel = zeros(TestSize,1);
    
    AllTrainLabel(1:size(TrainData{a},1))=1;
    AllValLabel(1:size(ValData{a},1))=1;
    AllTestLabel(1:size(TestData{a},1))=1;
    
    %AllTrainLabel(1+size(TrainData{a},1):end)=-1;
    %AllValLabel(1+size(ValData{a},1):end)=-1;
    %AllTestLabel(1+size(TestData{a},1):end)=-1;

    
    inputs = [AllTrainData;AllValData;AllTestData]';
    targets = [AllTrainLabel;AllValLabel;AllTestLabel]';
    
    % Create a neuron{i}
    neurons{i} = perceptron;
    
    % Setup Division of Data for Training, Validation, Testing
    % For a list of all data division functions type: help nndivide
    
    neurons{i}.divideFcn = 'divideind';
    neurons{i}.divideMode = 'sample';  % Divide up every sample
    neurons{i}.divideParam.trainInd = 1:TrainSize;
    neurons{i}.divideParam.valInd = TrainSize+1:TrainSize+ValSize;
    neurons{i}.divideParam.testInd = TrainSize+ValSize+1:TrainSize+ValSize+TestSize;
    
    % Choose Plot Functions
    % For a list of all plot functions type: help nnplot
    neurons{i}.plotFcns = {'plotperform','plottrainstate','ploterrhist', ...
        'plotregression', 'plotfit','plotconfusion','plotroc'};

    % Train the neuron{i}work
    [neurons{i},tr] = train(neurons{i},inputs,targets);
    
    % Test the neuron{i}work
    outputs = neurons{i}(inputs);
    %errors = gsubtract(targets,outputs);
    %performance = perform(neuron{i},targets,outputs)
    
    % Recalculate Training, Validation and Test Performance
    trainTargets = targets .* tr.trainMask{1};
    valTargets = targets  .* tr.valMask{1};
    testTargets = targets  .* tr.testMask{1};
    trainPerformance{i} = perform(neurons{i},trainTargets,outputs);
    valPerformance{i} = perform(neurons{i},valTargets,outputs);
    testPerformance{i} = perform(neurons{i},testTargets,outputs);
    
    % View the neuron{i}work
%    view(neurons{i})
    
    % Plots
    % Uncomment these lines to enable various plots.
    %figure, plotperform(tr)
    %figure, plottrainstate(tr)
    %figure, plotconfusion(testTargets,outputs)
    %figure, ploterrhist(errors)
    
    
end

%Confusion Matrix
ConfMat(1:3,1:3) = 0;
%Classification Accuracy
Accu(1:3) = 0;
for i = 1:3
        classlabel = getClass(TestData{i},neurons,neuronsClasses);
        for j=1:3
            ConfMat(i,j) = ConfMat(i,j) + sum(classlabel==j);    
        end
Accu(i) = ConfMat(i,i) / sum(ConfMat(i,:));        
end
disp('Confusion Matrix');
disp(ConfMat);
disp('Classification Accuracy');
disp(Accu);

disp('Average Accuracy');
disp(mean(Accu));
plotClassifer(TrainData,neurons,neuronsClasses)
end

function [Z] = decisionSurf(X,Y,class,neurons,neuronsLabel)
Z=(getClass([X Y],neurons,neuronsLabel) == class);
end

function [class] = getClass(X,neurons,neuronsLabel)
output=zeros(size(X,1),3);
for i = 1:3
    op = neurons{i}(X');
    output(op' == 1,i) = neuronsLabel{i}(1);
    output(op' == 0,i) = neuronsLabel{i}(2);
end
class = mode(output,2);
end

function plotClassifer(TrainData,neurons,neuronsLabel)
%{

PLOTCLASSIFIER - Function to plot the data and decision boundaries.
ClassA,ClassB,ClassC - Tarin data
gA,gB,gC - handle to decision surface
%}

cmap = hsv(5);

figure;
AllData = cell2mat(TrainData')';
xmin = min(AllData(1,:)) - 1;
xmax = max(AllData(1,:)) + 1;
ymin = min(AllData(2,:)) - 1;
ymax = max(AllData(2,:)) + 1;


hold on;
for i = 1:3
    ClassData = TrainData{i}';
    scatter3(ClassData(1,:),ClassData(2,:),ones(1,size(ClassData,2)), ...
        'd','filled','MarkerFaceColor',cmap(i,:));
end

s = warning('off','all');

for i = 1:3
    %syms x y;
    [x,y] = meshgrid(xmin:0.5:xmax,ymin:0.5:ymax);
    %g = @(x,y)(decisionSurf(x,y,i,neurons,neuronsLabel));
    %gplot = ezsurf(g,[xmin,xmax,ymin,ymax]);
    %z = decisionSurf(x,y,i,neurons,neuronsLabel);
    z=zeros(size(x));
    for j = 1:size(x,2)
        z(:,j)=decisionSurf(x(:,j),y(:,j),i,neurons,neuronsLabel);
    end
    surf(x,y,z)
    gplot = surf(x,y,z);
    set(gplot, 'FaceColor', [1 1 1]-cmap(i,:));
    hold on;
end
warning(s);

xlabel('x');
ylabel('y');

end