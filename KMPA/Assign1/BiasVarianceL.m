function BiasVarianceL
N = 1000; % # OF OBSERVATIONS PER DATASET
K = 5;% # OF DATASETS
noiseSTD = 1; % NOISE STANDARDE DEV.
nTrain = ceil(N*.9); % # OF TRAINING POINTS


stepL =1;
maxL = 0;
minL = -50;

logL=minL:stepL:maxL;
lamdas = exp(logL);
nLamdas=size(lamdas,2);

M = 10;

% # INITIALIZE SOME VARIABLES
weights = cell(nLamdas,K);
yTrain = cell(1,nLamdas);
yTest = cell(1,nLamdas);
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
    for l = 1:nLamdas
 
        % MODEL PARAMETER ESTIMATES
        weights{l,iS} = compW(trainData,trainTarget,M,lamdas(l));
        % PREDICTIONS
        yTrain {l}(iS,:) = getY(weights{l,iS},trainData,M)'; %TRAINING SET
        yTest {l}(iS,:) = getY(weights{l,iS},testData,M)'; % TESTING SET
 
        % MEAN SQUARED ERROR
        %trainErrors{l}(iS) = mean((yTrain{l}(iS,:)' - trainTarget).^2); % TRAINING
        testErrors{l}(iS) = mean((yTest{l}(iS,:)' - testTarget).^2); % TESTING
    end
end
 
% CALCULATE AVERAGE PREDICTION ERROR, BIAS, AND VARIANCE

target=exp(cos(2*pi*testData))+log(testData);

for iD = 1:nLamdas
    %trainError(iD) = mean(trainErrors{iD});
    testError(iD) = mean(testErrors{iD});
    biasSquared(iD) = mean((mean(yTest{iD})-target').^2);
    variance(iD) = mean(var(yTest{iD},1));
end
 
% DISPLAY
figure;
hold on;
plot(logL,testError,'k','Linewidth',2);
plot(logL,biasSquared,'r','Linewidth',2);
plot(logL,variance,'b','Linewidth',2);
plot(logL,biasSquared + variance,'m-.','Linewidth',2);
xlabel('log(lambda)')
legend('Test Error','Bias^2','Variance','Bias^2+Var.')
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