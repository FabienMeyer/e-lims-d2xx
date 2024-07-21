"""e_lims_d2xx tests."""

import pytest

from e_lims_d2xx import e_lims_d2xx


@pytest.fixture()
def name() -> str:
    """Sample pytest fixture.

    See more at: http://doc.pytest.org/en/latest/fixture.html
    """
    return 'World'


def test_content(name: str) -> None:
    """Sample pytest test function with the pytest fixture as an argument."""
    assert 'Hello World' in e_lims_d2xx.hello(name)
