function [ x ] = normalize( x )
%
x = bsxfun(@rdivide,x,sum(x,2));
x(~isfinite(x)) = 1; 
end

