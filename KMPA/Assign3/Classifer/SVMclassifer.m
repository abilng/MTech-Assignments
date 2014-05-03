function [model] = SVMclassifer(DataRoot,NClass,SVMtype,kernal,gamma,coef0,degree)

if nargin < 2
    error('Not Enough Arguments');
end

CrossVal = true;

if ~exist('SVMtype','var')
    SVMtype = 0;
end

if ~exist('kernal','var')
    kernal = 0;
end


SVMarg = [];

switch (SVMtype)
    case {0,'CSVM'}
        SVMtype = 0;
        SVMarg = [ SVMarg ,' -s 0'];
    case {1,'NSVM'}
        SVMtype = 1;
        SVMarg = [ SVMarg ,' -s 1'];
    otherwise
        error('Unknown SVM type');
end

switch (kernal)
    case {0,'linear'}
        SVMarg = [ SVMarg ,' -t 0'];
    case {1,'poly'}
        SVMarg = [ SVMarg ,' -t 1'];
        if exist('gamma','var')
            SVMarg = [ SVMarg ,' -g ',num2str(gamma)];
        end
        if exist('coef0','var')
            SVMarg = [ SVMarg ,' -r ',num2str(coef0)];
        end
        if exist('degree','var')
            SVMarg = [ SVMarg ,' -d ',num2str(degree)];
        end
    case {2,'gaussian'}
        SVMarg = [ SVMarg ,' -t 2'];
        if exist('gamma','var')
            SVMarg = [ SVMarg ,' -g ',num2str(gamma)];
        end
    case {3,'precomputed'}
        SVMarg = [ SVMarg ,' -t 4'];
    otherwise
        error('Unknown Kernal type');
end




AllTrainData= [];
AllTestData = [];
AllValData  = [];
AllTrainLabel= [];
AllTestLabel = [];
AllValLabel  = [];

for i=1:NClass
    TrainData = load(strcat(DataRoot,'/class',int2str(i),'_train.txt'));
    TrainLabel = zeros(size(TrainData,1),1);
    TrainLabel(:) = i;
    TestData = load(strcat(DataRoot,'/class',int2str(i),'_test.txt'));
    TestLabel = zeros(size(TestData,1),1);
    TestLabel(:) = i;
    ValData = load(strcat(DataRoot,'/class',int2str(i),'_val.txt'));
    ValLabel = zeros(size(ValData,1),1);
    ValLabel(:) = i;
    
    AllTrainData = [AllTrainData;TrainData]; %#ok<AGROW>
    AllValData = [AllValData;ValData]; %#ok<AGROW>
    AllTestData = [AllTestData;TestData]; %#ok<AGROW>
    
    AllTrainLabel = [AllTrainLabel;TrainLabel]; %#ok<AGROW>
    AllValLabel = [AllValLabel;ValLabel]; %#ok<AGROW>
    AllTestLabel = [AllTestLabel;TestLabel]; %#ok<AGROW>
    
end

dim=size(AllTrainData,2);

fprintf('\nSelction of C/nu using Cross Validaition\n');
%# Cross Validation on C/nu
if CrossVal
    if SVMtype == 0
        C = crossValidtaion(-2:1:10,AllTrainData,AllTrainLabel,AllValData,AllValLabel,SVMarg,0);
        SVMarg = [ SVMarg ,' -c ' num2str(C) ];
    else
        C = crossValidtaion(0.01:0.01:0.25,AllTrainData,AllTrainLabel,AllValData,AllValLabel,SVMarg,1);
        SVMarg = [ SVMarg ,' -n ',num2str(C) ];
    end
else
    if SVMtype == 0  %#ok<UNRCH>
        C = 1 %#ok<NOPRT> 
        SVMarg = [ SVMarg ,' -c ' num2str(C) ];
    else
        C = 0.07 %#ok<NOPRT>
        SVMarg = [ SVMarg ,' -n ',num2str(C) ];
    end
end

% #######################
% Train the SVM in one-vs-rest (OVR) mode
% #######################
fprintf('\nTraning SVM\n');
model = ovrtrain(AllTrainLabel, AllTrainData, SVMarg);
% #######################
% Classify samples using OVR model
% #######################

fprintf('\nTesting SVM\n');
[predict_label, accuracy, ~] = ovrpredict(AllTestLabel, AllTestData, model);
fprintf('Accuracy = %g%%\n', accuracy * 100);

% plot confusionmat
plotconfMat(AllTestLabel,predict_label,NClass)


if dim==2
    fprintf('Ploting Decision regions\n');
    plotClassifer(AllTrainData,AllTrainLabel,model,NClass,C)
end
end

function plotconfMat(TargetLabel,OutputLabel,NClass)
ALabel = zeros(size(OutputLabel,1),NClass);
PLabel = zeros(size(OutputLabel,1),NClass);
for k=1:NClass
    ALabel(TargetLabel==k,k) = 1;
    PLabel(OutputLabel==k,k) = 1;
end

plotconfusion(ALabel',PLabel');
%C = confusionmat(AllTestLabel,predict_label);
%disp(C);
end


function plotClassifer(Data,Label,model,NClass,C)
%{

PLOTCLASSIFIER - Function to plot the data and decision boundaries.
ClassA,ClassB,ClassC - Tarin data
gA,gB,gC - handle to decision surface
%}

figure;

xmin = min(Data(:,1))-1;
ymin = min(Data(:,2))-1;
xmax = max(Data(:,1))+1;
ymax = max(Data(:,2))+1;

M = length(model.models);
cmap = hsv(NClass);

hold on;
legendText = cell(1,2*NClass+2*M);
for i = 1:NClass
    ClassData = Data(Label==i,:);
    scatter3(ClassData(:,1),ClassData(:,2),ones(size(ClassData,1),1).*20, ...
        10,cmap(i,:),'MarkerFaceColor',cmap(i,:));
    legendText{i} = ['Train Data - class ' int2str(i)];
end


for i=1:NClass
    g = @(X,Y)(decisionSurf(X,Y,i,model));
    %g = @(X,Y)(ovrpredictBot(zeros(size(X)),[X Y],model) == i);
    %diary on;
    %for j = 1:size(x,2)
    %    z(:,j)=g(x(:,j),y(:,j));
    %end
    %diary off;
    %gplot = surf(x,y,z);
    %set(gplot, 'FaceColor', [1 1 1]-cmap(i,:));
    
    
    gplot = ezsurf(g,[xmin,xmax,ymin,ymax]);
    set(gplot, 'FaceColor', [1 1 1]-cmap(i,:));
    hold on;
    legendText{NClass+i} = ['Decision region for class ' int2str(i)];
end

cmap = lines(NClass);
i=1;
AllSV = [];
%B = [1.065643,0.940833,1.098245];
for m=1:M
    %C=B(m);
    SV=full(model.models{m}.SVs);
    alpha=abs(model.models{m}.sv_coef);
    nBV=sum(abs(alpha-C)<=eps);
    nUBV=sum(abs(alpha-C)>eps);
    
    scatter3(SV(abs(alpha-C)>eps,1),SV(abs(alpha-C)>eps,2),ones(nUBV,1).*20, ...
        20+100*m,'o','MarkerEdgeColor',cmap(m,:),'LineWidth',1.5);
    legendText{2*NClass+i} = ['Unbounded Support Vector (SVM -', int2str(m),')'] ;
    i=i+1;
    if nBV >0
        scatter3(SV(abs(alpha-C)<=eps,1),SV(abs(alpha-C)<=eps,2),ones(nBV,1).*20, ...
            20+100*m,'d','MarkerEdgeColor',cmap(m,:),'LineWidth',1.5);
        legendText{2*NClass+i} = ['Bounded Support Vector (SVM -', int2str(m),')'] ;
        i=i+1;
    end
    AllSV = [AllSV; SV]; %#ok<AGROW>
end
TotalSV = size(unique(AllSV,'rows'),1);
fprintf('Total No of SV=%d\n',TotalSV);

legend(legendText{1:2*NClass+i-1});
title('Decision Region');
end




function op = decisionSurf(x,y,i,model)
D = ovrpredictBot(zeros(size(x)),[x y],model);
op = D(:,i);
end


function [decv_out] = ovrpredictBot(y, x, model)

labelSet = model.labelSet;
labelSetSize = length(labelSet);
models = model.models;
observationSize = size(y, 1);

decv_out = zeros(observationSize,labelSetSize);

for i=1:labelSetSize
    [~,~,decv_out(:,i)] = svmpredict(double(y == labelSet(i)), x, models{i},' -q');
    % Here we have to do some strange thing...
    % IF models{i}.Label(1) == 1, the decv_out is stored as it is
    % But if models{i}.Label(1) == 0, the decv_out is multiplied by -1 before
    % stored.
    % After doing this process the decision values are correct!!!
    decv_out(:,i) = decv_out(:,i) * (2 * models{i}.Label(1) - 1);
end
end


function bestc = crossValidtaion(Range,TrainData,TrainLabel,ValData,ValLabel,SVMArg,type)
if (type == 0)
    cmd = ' -c ';
    bestcv = 0;
    for log2c = Range,
        param  = [SVMArg, cmd, num2str(2^log2c)];
        model = ovrtrain(TrainLabel,TrainData,[param ,' -q']);
        [~, cv, ~]  = ovrpredict(ValLabel,ValData,model,'-q');
        if (cv >= bestcv),
            bestcv = cv; bestc = 2^log2c;
        end
    end
    fprintf('\n best c=%g, rate=%g\n', bestc,bestcv);
else
    cmd = ' -n ';
    bestcv = 0;
    for nu = Range,
        param  = [SVMArg, cmd, num2str(nu)];
        model = ovrtrain(TrainLabel,TrainData,[param ,' -q']);
        [~, cv, ~]  = ovrpredict(ValLabel,ValData,model,'-q');
        if (cv > bestcv),
            bestcv = cv; bestc = nu;
        end
    end
    fprintf('\n best nu=%g, rate=%g\n', bestc,bestcv);
end

end
