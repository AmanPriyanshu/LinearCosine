from ._linear_cosine import cosine_similarity as _cosine_similarity

def cosine_similarity(v1, v2, mantissa_bits=8, use_lmul=True):
    return _cosine_similarity(v1, v2, mantissa_bits, use_lmul)