function [model] = SVMclassifer2(DataRoot,SVMtype,kernal,gamma,coef0,degree)

if nargin < 1
    error('Not Enough Arguments');
end

if ~exist('SVMtype','var')
    SVMtype = 0;
end

if ~exist('kernal','var')
    kernal = 0;
end

NClass = 2;
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
    TrainLabel(:) = i;%(-1).^(i-1);
    TestData = load(strcat(DataRoot,'/class',int2str(i),'_test.txt'));
    TestLabel = zeros(size(TestData,1),1);
    TestLabel(:) = i;%(-1).^(i-1);
    ValData = load(strcat(DataRoot,'/class',int2str(i),'_val.txt'));
    ValLabel = zeros(size(ValData,1),1);
    ValLabel(:) = i;%(-1).^(i-1);
    
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
if SVMtype == 0
    C = crossValidtaion(-1:1:3,AllTrainData,AllTrainLabel,AllValData,AllValLabel,SVMarg,0);
    SVMarg = [ SVMarg ,' -c ' num2str(C) ];
else
    C = crossValidtaion(0.1:0.1:0.7,AllTrainData,AllTrainLabel,AllValData,AllValLabel,SVMarg,1);
    SVMarg = [ SVMarg ,' -n ',num2str(C) ];
end


% #######################
% Train the SVM
% #######################
fprintf('\nTraning SVM\n');
model = svmtrain(AllTrainLabel, AllTrainData, SVMarg);
% #######################
% Classify samples using svm model
% #######################

fprintf('\nTesting SVM\n');
[predict_label, accuracy, ~] = svmpredict(AllTestLabel, AllTestData, model);
fprintf('Accuracy = %g%%\n', accuracy * 100);

% plot confusionmat
plotconfMat(AllTestLabel,predict_label)


if dim==2
    fprintf('Ploting Decision regions\n');
    plotClassifer(AllTrainData,AllTrainLabel,model,C)
end
end

function plotconfMat(TargetLabel,OutputLabel)
ALabel = zeros(size(OutputLabel,1),2);
PLabel = zeros(size(OutputLabel,1),2);
for k=1:2
    ALabel(TargetLabel==k,k) = 1;
    PLabel(OutputLabel==k,k) = 1;
end

plotconfusion(ALabel',PLabel');
%C = confusionmat(AllTestLabel,predict_label);
%disp(C);
end


function plotClassifer(Data,Label,model,C)
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


cmap = hsv(2);

hold on;
legendText = cell(1,2*2+2);
for i = 1:2
    ClassData = Data(Label==i,:);
    scatter3(ClassData(:,1),ClassData(:,2),ones(size(ClassData,1),1).*20, ...
        10,cmap(i,:),'MarkerFaceColor',cmap(i,:));
    legendText{i} = ['Train Data - class ' int2str(i)];
end


for i=1:2
    g = @(X,Y)(decisionSurf(X,Y,i,model));
    gplot = ezsurf(g,[xmin,xmax,ymin,ymax]);
    set(gplot, 'FaceColor', [1 1 1]-cmap(i,:));
    hold on;
    legendText{2+i} = ['Decision region for class ' int2str(i)];
end



SV=full(model.SVs);
alpha=abs(model.sv_coef);
nBV=sum((alpha-C)<=eps);
nUBV=sum((alpha-C)>eps);

scatter3(SV((alpha-C)>eps,1),SV((alpha-C)>eps,2),ones(nUBV,1).*20, ...
    100,'o','MarkerEdgeColor','k','LineWidth',1.5);
legendText{5} = 'Unbounded Support Vector' ;
if nBV >0
    scatter3(SV((alpha-C)<=eps,1),SV((alpha-C)<=eps,2),ones(nBV,1).*20, ...
        100,'d','MarkerEdgeColor','k','LineWidth',1.5);
    legendText{6} = 'Bounded Support Vector ' ;
    legend(legendText{1:6});
else
    legend(legendText{1:5});
end

fprintf('Total No of SV=%d\n',sum(model.nSV));
title('Decision Region');
end




function op = decisionSurf(x,y,i,model)
[~,~,D] = svmpredict(zeros(size(x)),[x y], model,'-q');
%op=(L==i);
op=D.*(-2*i + 1);

end



function bestc = crossValidtaion(Range,TrainData,TrainLabel,ValData,ValLabel,SVMArg,type)
if (type == 0)
    cmd = ' -c ';
    bestcv = 0;
    for log2c = Range,
        param  = [SVMArg, cmd, num2str(2^log2c)];
        model = svmtrain(TrainLabel,TrainData,[param ,' -q']);
        [~, cv, ~]  = svmpredict(ValLabel,ValData,model,' -q');
        if (cv(1) > bestcv),
            bestcv = cv(1); bestc = 2^log2c;
        end
    end
    fprintf('\n best c=%g, rate=%g\n', bestc,bestcv);
else
    cmd = ' -n ';
    bestcv = 0;
    for nu = Range,
        param  = [SVMArg, cmd, num2str(nu)];
        model = svmtrain(TrainLabel,TrainData,[param ,' -q']);
        [~, cv, ~]  = svmpredict(ValLabel,ValData,model,' -q');
        if (cv(1) > bestcv),
            bestcv = cv(1); bestc = nu;
        end
    end
    fprintf('\n best nu=%g, rate=%g\n', bestc,bestcv);
end

end
