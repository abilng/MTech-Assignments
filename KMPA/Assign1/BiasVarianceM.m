function BiasVarianceM
N = 1000; % # OF OBSERVATIONS PER DATASET
K = 5;% # OF DATASETS
noiseSTD = 1; % NOISE STANDARDE DEV.
nTrain = ceil(N*.9); % # OF TRAINING POINTS
nPolyMax = 28; % MAXIMUM MODEL COMPLEXITY
 
% # INITIALIZE SOME VARIABLES
weights = cell(nPolyMax,K);
yTrain = cell(1,nPolyMax);
yTest = cell(1,nPolyMax);
x=rand(N,1);
warning('off');
for iS = 1:K % LOOP OVER DATASETS
    % CREATE OBSERVED DATA, y
    y = exp(cos(2*pi*x))+log(x) + noiseSTD*randn(size(x));
 
    % CREATE TRAINING SET
    trainData = x(1:nTrain);
    trainTarget = y(1:nTrain);
 
    % CREATE TESTING SET
    testData = x(nTrain+1:end);
    testTarget = y(nTrain+1:end);
 
    % FIT MODELS
    for M = 1:nPolyMax
 
        % MODEL PARAMETER ESTIMATES
        weights{M,iS} = compW(trainData,trainTarget,M,0);
        % PREDICTIONS
        yTrain {M}(iS,:) = getY(weights{M,iS},trainData,M)'; %TRAINING SET
        yTest {M}(iS,:) = getY(weights{M,iS},testData,M)'; % TESTING SET
 
        % MEAN SQUARED ERROR
        %trainErrors{M}(iS) = mean((yTrain{M}(iS,:)' - trainTarget).^2); % TRAINING
        testErrors{M}(iS) = mean((yTest{M}(iS,:)' - testTarget).^2); % TESTING
    end
end
 
% CALCULATE AVERAGE PREDICTION ERROR, BIAS, AND VARIANCE

target=exp(cos(2*pi*testData))+log(testData);

for iD = 1:nPolyMax
    %trainError(iD) = mean(trainErrors{iD});
    testError(iD) = mean(testErrors{iD});
    biasSquared(iD) = mean((mean(yTest{iD})-target').^2);
    variance(iD) = mean(var(yTest{iD},1));
end
[~,bestModel] = min(testError);
 
% DISPLAY
figure;
hold on;
plot(testError,'k','Linewidth',2);
plot(biasSquared,'r','Linewidth',2);
plot(variance,'b','Linewidth',2);
plot(biasSquared + variance,'m-.','Linewidth',2);
%yl = ylim;
%plot([bestModel,bestModel],[yl(1),yl(2)],'k--');
xlim([1,nPolyMax]);
xlabel('Model Complexity (Polynomial Order)')
legend('Test Error','Bias^2','Variance','Bias^2+Var')%,'Best Model')
hold off;

end

function w = compW(data, target,complexity,lamda)
phi = dMat(data,complexity);
%warning off;
w = ((lamda * eye(complexity)) + phi'*phi)\(phi'*target);
end

%% Function for creating Design Matrix

function phi = dMat(data,complexity)
phi = bsxfun(@power , data , (0:complexity-1));
end

function y = getY(w,data,complexity)
phi = dMat(data,complexity);
y = phi*w;
end