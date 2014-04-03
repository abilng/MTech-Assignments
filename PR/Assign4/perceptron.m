function [W] = perceptron(trainData,trainLabel,nClass)

 %W(1:nClass,1:size(trainData,2)+1) = 0.001; % agumented wt vector
 W = rand(nClass,size(trainData,2)+1);
 X = [ones(size(trainData),1) ,trainData]; % agumented train vector
% eta = 1;
 oldE = 0;
 minE = inf;
 minW = W;
 minI = 0;
 for iteration = 1 : 1000%0  %<- max iteration!
    eta = 1/iteration;
    Z=X*W';
    [~,newLabel]=max(Z,[],2); 
    for i = 1 : size(X,1)
        label = newLabel(i);
        actual = trainLabel(i);
        %W(label,:) = W(label,:) + X(i,:)*(Z(i,label)-Z(i,actual));
        if label ~= actual %wrong decision?
           W(label,:) = W(label,:) - eta*X(i,:);
           W(actual,:) = W(actual,:) + eta*X(i,:);
        end
    end
    E = sum(newLabel~=trainLabel')/size(X,1);
    %disp(E);
    if(E<minE)
        minE = E;
        minW = W;
        minI = iteration ;
    end
    if abs(E-oldE) < 1e-5
        break;
    end
    oldE = E;
 end
 W = minW;
 fprintf('After %d(%f) iteration\n',minI,minE);
end