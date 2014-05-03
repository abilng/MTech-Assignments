function K = kernalGram(X1, X2, kernelFun, param1, param2,param3)
%GRAM Computes the Gram-matrix of data points X using a kernel function
%
% Linear kernel: G = gram(X1,X2,'linear')
% Gaussian kernel: G = gram(X1,X2,'gauss', w)
% Polynomial kernel: G = gram(X1,X2,'poly',a,b,c)
%
%

if (nargin < 3),
    error('Not enough input arguments');
end;

if size(X1, 2) ~= size(X2, 2)
    error('Dimensionality of both datasets should be equal');
end

switch (kernelFun)
    % Linear kernel
    case 'linear'
        K = X1 * X2';
        
        % Gaussian kernel
    case 'gauss'
        if (nargin < 4),
            error('Not enough input arguments');
        end;
        gamma=param1;
        K = dist(X1, X2');
        K = exp(-gamma.*(K.^2));
        
        % Polynomial kernel
    case 'poly'
        if (nargin < 6),
            error('Not enough input arguments');
        end;
        a = param1;
        b = param2;
        p = param3;
        K = (a+(X1 * X2').*b) .^ p;
        
   case 'npoly'
        if (nargin < 6),
            error('Not enough input arguments');
        end;
        a = param1;
        b = param2;
        p = param3;
        K = (a+(X1 * X2').*b) .^ p;
        s1=sqrt((a+sum((X1.*X1),2).*b).^ p);
        s2=sqrt((a+sum((X2.*X2),2).*b).^ p);
        [I,J]=size(K);
        Kn = zeros(I,J);
        for i = 1:I
            for j= 1:J
            Kn(i,j) = abs(K(i,j))/(s1(i).*s2(j));
            end
        end
        K = Kn;
    otherwise
        error('Unknown kernel function.');
end
end