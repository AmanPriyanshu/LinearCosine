from ._linear_cosine import cosine_similarity as _cosine_similarity

def cosine_similarity(v1, v2, mantissa_bits=8, use_lmul=True):
    """
    Compute cosine similarity using either linear or standard multiplication.

    Args:
    v1 (list): First input vector
    v2 (list): Second input vector
    mantissa_bits (int): Number of mantissa bits to use (default: 8)
    use_lmul (bool): Whether to use linear multiplication (default: True)

    Returns:
    float: Cosine similarity between v1 and v2
    """
    return _cosine_similarity(v1, v2, mantissa_bits, use_lmul)