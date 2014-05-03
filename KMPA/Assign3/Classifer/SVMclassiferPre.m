function [model] = SVMclassiferPre(NClass,TrainKernal,TrainLabel, ...
    ValKernal,ValLabel,TestKernal,TestLabel,CrossVal)

if nargin == 7
    CrossVal = true;
end

ValKernal = [(1:size(ValKernal,2))', ValKernal'];
TestKernal = [(1:size(TestKernal,2))', TestKernal'];
TrainKernal = [(1:size(TrainKernal,2))', TrainKernal'];


SVMarg = ' -s 0 -t 4'; %CSVM,'precomputed'

% #####################
% Cross Validation on C
% #####################
fprintf('\nSelction of C using Cross Validaition\n');
if CrossVal
    C = crossValidtaion(-2:1:10,TrainKernal,TrainLabel,ValKernal,ValLabel,SVMarg);
else
    C = 1;
    fprintf('C = %f\n',C);    
end
SVMarg = [ SVMarg ,' -c ' num2str(C) ];


% #######################
% Train the SVM in one-vs-rest (OVR) mode
% #######################
fprintf('\nTraning SVM\n');
model = ovrtrain(TrainLabel, TrainKernal, SVMarg);
% #######################
% Classify samples using OVR model
% #######################

fprintf('\nTesting SVM\n');
[predict_label, accuracy, ~] = ovrpredict(TestLabel, TestKernal, model);
fprintf('Accuracy = %g%%\n', accuracy * 100);

% plot confusionmat
plotconfMat(TestLabel,predict_label,NClass)

end

function plotconfMat(TargetLabel,OutputLabel,NClass)
ALabel = zeros(size(OutputLabel,1),NClass);
PLabel = zeros(size(OutputLabel,1),NClass);
for k=1:NClass
    ALabel(TargetLabel==k,k) = 1;
    PLabel(OutputLabel==k,k) = 1;
end

plotconfusion(ALabel',PLabel');
%C = confusionmat(TestLabel,predict_label);
%disp(C);
end


function bestc = crossValidtaion(Range,TrainData,TrainLabel,ValData,ValLabel,SVMArg)

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
end
