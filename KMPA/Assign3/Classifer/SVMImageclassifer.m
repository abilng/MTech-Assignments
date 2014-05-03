function [model] = SVMImageclassifer(DataRoot,NClass,SVMtype,gamma)

if nargin < 2
    error('Not Enough Arguments');
end

CrossVal = true;

if ~exist('SVMtype','var')
    SVMtype = 0;
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



SVMarg = [ SVMarg ,' -t 2'];
if exist('gamma','var')
    SVMarg = [ SVMarg ,' -g ',num2str(gamma)];
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
    
    TrainData = normr(TrainData);
    TestData = normr(TestData);
    ValData = normr(ValData);
    
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
        C = 1 ;
        fprintf('C = %f\n',C);  
        SVMarg = [ SVMarg ,' -c ' num2str(C) ];
    else
        C = 0.1 ;
        fprintf('Nu = %f\n',C);  
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
